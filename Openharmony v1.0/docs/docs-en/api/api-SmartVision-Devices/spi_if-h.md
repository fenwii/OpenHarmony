# spi\_if.h<a name="EN-US_TOPIC_0000001054718105"></a>

## **Overview**<a name="section1085515267093527"></a>

**Related Modules:**

[SPI](spi.md)

**Description:**

Defines standard SPI-specific interfaces for driver development. 

A driver needs to use the SPI-specific interfaces for data writing and reading before performing any operations on an SPI-compliant device.

**Since:**

1.0

## **Summary**<a name="section768224834093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table168742597093527"></a>
<table><thead align="left"><tr id="row1512900548093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1772806573093527"><a name="p1772806573093527"></a><a name="p1772806573093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1369919995093527"><a name="p1369919995093527"></a><a name="p1369919995093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1409435938093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p600594942093527"><a name="p600594942093527"></a><a name="p600594942093527"></a><a href="spidevinfo.md">SpiDevInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p325436427093527"><a name="p325436427093527"></a><a name="p325436427093527"></a>Defines the general SPI device descriptor, which can be used as the unique identifier of an SPI device. When operating an SPI device, you need to specify a descriptor of the <a href="spidevinfo.md">SpiDevInfo</a> type, and obtain the handle of the SPI device by calling <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </p>
</td>
</tr>
<tr id="row692333337093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1321650928093527"><a name="p1321650928093527"></a><a name="p1321650928093527"></a><a href="spimsg.md">SpiMsg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1700013246093527"><a name="p1700013246093527"></a><a name="p1700013246093527"></a>Defines the custom SPI transfer message. </p>
</td>
</tr>
<tr id="row1253674709093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091256253093527"><a name="p2091256253093527"></a><a name="p2091256253093527"></a><a href="spicfg.md">SpiCfg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449036053093527"><a name="p449036053093527"></a><a name="p449036053093527"></a>Defines the configuration of an SPI device. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table739134076093527"></a>
<table><thead align="left"><tr id="row464382079093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p517847462093527"><a name="p517847462093527"></a><a name="p517847462093527"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1661572641093527"><a name="p1661572641093527"></a><a name="p1661572641093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row868046486093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1545306063093527"><a name="p1545306063093527"></a><a name="p1545306063093527"></a><a href="spi.md#ga430ad9ccffd42f4427ba22fcc8167c64">SPI_CLK_PHASE</a>   (1 &lt;&lt; 0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298008591093527"><a name="p298008591093527"></a><a name="p298008591093527"></a>Indicates the SPI clock phase. The value <strong id="b1805599228093527"><a name="b1805599228093527"></a><a name="b1805599228093527"></a>0</strong> indicates that data will be sampled on the first clock edge, and <strong id="b1625533193093527"><a name="b1625533193093527"></a><a name="b1625533193093527"></a>1</strong> indicates that data will be sampled on the second clock edge. </p>
</td>
</tr>
<tr id="row1026536706093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p626812110093527"><a name="p626812110093527"></a><a name="p626812110093527"></a><a href="spi.md#ga4cafe948918622f80c27db640c6c23c6">SPI_CLK_POLARITY</a>   (1 &lt;&lt; 1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p752687059093527"><a name="p752687059093527"></a><a name="p752687059093527"></a>Indicates the SPI clock polarity. The value <strong id="b760995577093527"><a name="b760995577093527"></a><a name="b760995577093527"></a>0</strong> indicates a low-level clock signal in the idle state, and <strong id="b1440316075093527"><a name="b1440316075093527"></a><a name="b1440316075093527"></a>1</strong> indicates a high-level clock signal in the idle state. </p>
</td>
</tr>
<tr id="row1566082770093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401673796093527"><a name="p1401673796093527"></a><a name="p1401673796093527"></a><a href="spi.md#ga11113e647ddd2101c1c693632f63aa7c">SPI_MODE_3WIRE</a>   (1 &lt;&lt; 2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1785050281093527"><a name="p1785050281093527"></a><a name="p1785050281093527"></a>Indicates that a single data line is used for both input and output. </p>
</td>
</tr>
<tr id="row1445479735093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p830610576093527"><a name="p830610576093527"></a><a name="p830610576093527"></a><a href="spi.md#ga8619b297de563eca6852af34c79daa62">SPI_MODE_LOOP</a>   (1 &lt;&lt; 3)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p715271392093527"><a name="p715271392093527"></a><a name="p715271392093527"></a>Indicates the SPI loopback mode. </p>
</td>
</tr>
<tr id="row559953218093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1573947038093527"><a name="p1573947038093527"></a><a name="p1573947038093527"></a><a href="spi.md#ga4da8777b0d2d7dd96d6038411791c36e">SPI_MODE_LSBFE</a>   (1 &lt;&lt; 4)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p38268436093527"><a name="p38268436093527"></a><a name="p38268436093527"></a>Indicates the SPI data transfer order. The value <strong id="b1857387175093527"><a name="b1857387175093527"></a><a name="b1857387175093527"></a>0</strong> indicates that data is transferred from the most significant bit (MSB) to the least significant bit (LSB), and <strong id="b950624559093527"><a name="b950624559093527"></a><a name="b950624559093527"></a>1</strong> indicates the opposite. </p>
</td>
</tr>
<tr id="row326063033093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139746966093527"><a name="p2139746966093527"></a><a name="p2139746966093527"></a><a href="spi.md#ga361195644b8e753d5469dd492c66217b">SPI_MODE_NOCS</a>   (1 &lt;&lt; 5)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699097746093527"><a name="p699097746093527"></a><a name="p699097746093527"></a>Indicates that there is only one SPI device, and no chip select (CS) is required. </p>
</td>
</tr>
<tr id="row344317221093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133853802093527"><a name="p2133853802093527"></a><a name="p2133853802093527"></a><a href="spi.md#ga33d89d81eb33b7a5de1a03e88279163d">SPI_MODE_CS_HIGH</a>   (1 &lt;&lt; 6)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402530544093527"><a name="p1402530544093527"></a><a name="p1402530544093527"></a>Indicates that the CS level is high when an SPI device is selected. </p>
</td>
</tr>
<tr id="row1651797657093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p238282886093527"><a name="p238282886093527"></a><a name="p238282886093527"></a><a href="spi.md#ga42f3ef9ad5429ac10662448fe1f5a746">SPI_MODE_READY</a>   (1 &lt;&lt; 7)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693715464093527"><a name="p1693715464093527"></a><a name="p1693715464093527"></a>Indicates that the SPI device is set to low for pausing data transfer. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1818789504093527"></a>
<table><thead align="left"><tr id="row2071986664093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1316055075093527"><a name="p1316055075093527"></a><a name="p1316055075093527"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1702628853093527"><a name="p1702628853093527"></a><a name="p1702628853093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2102400759093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p304953365093527"><a name="p304953365093527"></a><a name="p304953365093527"></a><a href="spi.md#ga55946d1d895fc2b7b33007019de1668f">SpiTransferMode</a> { <a href="spi.md#gga55946d1d895fc2b7b33007019de1668fad91925d3e1b3e82ff14004dd0b9d98a3">SPI_INTERRUPT_TRANSFER</a> = 0, <a href="spi.md#gga55946d1d895fc2b7b33007019de1668fa51d9bac6c8cbf4d95705563b097bb0b2">SPI_POLLING_TRANSFER</a>, <a href="spi.md#gga55946d1d895fc2b7b33007019de1668fad4d2e8d82f1d9a15198399d6540bacd1">SPI_DMA_TRANSFER</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1792310132093527"><a name="p1792310132093527"></a><a name="p1792310132093527"></a>Enumerates transfer modes of SPI data. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1140787845093527"></a>
<table><thead align="left"><tr id="row487669440093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1193489648093527"><a name="p1193489648093527"></a><a name="p1193489648093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p497023671093527"><a name="p497023671093527"></a><a name="p497023671093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1240379880093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1185178561093527"><a name="p1185178561093527"></a><a name="p1185178561093527"></a><a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a> (const struct <a href="spidevinfo.md">SpiDevInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p528264086093527"><a name="p528264086093527"></a><a name="p528264086093527"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1107997835093527"><a name="p1107997835093527"></a><a name="p1107997835093527"></a>Obtains the handle of an SPI device. </p>
</td>
</tr>
<tr id="row1670343611093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1339525192093527"><a name="p1339525192093527"></a><a name="p1339525192093527"></a><a href="spi.md#gad5b082d6d0699a9bc5240d6a5491f08a">SpiClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432144908093527"><a name="p1432144908093527"></a><a name="p1432144908093527"></a>void </p>
<p id="p1858896005093527"><a name="p1858896005093527"></a><a name="p1858896005093527"></a>Releases the handle of an SPI device. </p>
</td>
</tr>
<tr id="row880979998093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027707973093527"><a name="p1027707973093527"></a><a name="p1027707973093527"></a><a href="spi.md#ga40e7274a4291f1482e720c956a291e9f">SpiTransfer</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="spimsg.md">SpiMsg</a> *msgs, uint32_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725831484093527"><a name="p1725831484093527"></a><a name="p1725831484093527"></a>int32_t </p>
<p id="p1925062623093527"><a name="p1925062623093527"></a><a name="p1925062623093527"></a>Launches a custom transfer to an SPI device. </p>
</td>
</tr>
<tr id="row1807092719093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p444208565093527"><a name="p444208565093527"></a><a name="p444208565093527"></a><a href="spi.md#gad7c852b1c6aed4380e393637aeb66802">SpiRead</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *buf, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053006582093527"><a name="p2053006582093527"></a><a name="p2053006582093527"></a>int32_t </p>
<p id="p50345262093527"><a name="p50345262093527"></a><a name="p50345262093527"></a>Reads data of a specified length from an SPI device. </p>
</td>
</tr>
<tr id="row1821324241093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p552686047093527"><a name="p552686047093527"></a><a name="p552686047093527"></a><a href="spi.md#ga77314bd5d40f78d97b25048b2e816ff9">SpiWrite</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *buf, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1162985995093527"><a name="p1162985995093527"></a><a name="p1162985995093527"></a>int32_t </p>
<p id="p432788656093527"><a name="p432788656093527"></a><a name="p432788656093527"></a>Writes data of a specified length to an SPI device. </p>
</td>
</tr>
<tr id="row990760181093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085305013093527"><a name="p2085305013093527"></a><a name="p2085305013093527"></a><a href="spi.md#ga0d8781e50042c5d89733d21097bec359">SpiSetCfg</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="spicfg.md">SpiCfg</a> *cfg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1448874130093527"><a name="p1448874130093527"></a><a name="p1448874130093527"></a>int32_t </p>
<p id="p187296781093527"><a name="p187296781093527"></a><a name="p187296781093527"></a>Sets configuration parameters for an SPI device. </p>
</td>
</tr>
<tr id="row128678419093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1293512203093527"><a name="p1293512203093527"></a><a name="p1293512203093527"></a><a href="spi.md#gabd835b51efecc8364c8b61914466d172">SpiGetCfg</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="spicfg.md">SpiCfg</a> *cfg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497023749093527"><a name="p497023749093527"></a><a name="p497023749093527"></a>int32_t </p>
<p id="p671918044093527"><a name="p671918044093527"></a><a name="p671918044093527"></a>Obtains the configuration parameters of an SPI device. </p>
</td>
</tr>
</tbody>
</table>

