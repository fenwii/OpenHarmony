# SPI<a name="EN-US_TOPIC_0000001055518038"></a>

## **Overview**<a name="section848977980093521"></a>

Defines standard APIs of the Serial Peripheral Interface \(SPI\) capabilities. 

The SPI module abstracts the SPI capabilities of different system platforms to provide stable APIs for driver development. This module can create and destroy SPI device handles, read and write SPI data, and obtain and set configuration parameters.

**Since:**

1.0

## **Summary**<a name="section1535953793093521"></a>

## Files<a name="files"></a>

<a name="table1524684272093521"></a>
<table><thead align="left"><tr id="row123239929093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p857345809093521"><a name="p857345809093521"></a><a name="p857345809093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p250557065093521"><a name="p250557065093521"></a><a name="p250557065093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row832581783093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567596929093521"><a name="p1567596929093521"></a><a name="p1567596929093521"></a><a href="spi_if-h.md">spi_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072162661093521"><a name="p2072162661093521"></a><a name="p2072162661093521"></a>Defines standard SPI-specific interfaces for driver development. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table678459692093521"></a>
<table><thead align="left"><tr id="row884264732093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2017062135093521"><a name="p2017062135093521"></a><a name="p2017062135093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2002391681093521"><a name="p2002391681093521"></a><a name="p2002391681093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row632433589093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1518776404093521"><a name="p1518776404093521"></a><a name="p1518776404093521"></a><a href="spidevinfo.md">SpiDevInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993777040093521"><a name="p993777040093521"></a><a name="p993777040093521"></a>Defines the general SPI device descriptor, which can be used as the unique identifier of an SPI device. When operating an SPI device, you need to specify a descriptor of the <a href="spidevinfo.md">SpiDevInfo</a> type, and obtain the handle of the SPI device by calling <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </p>
</td>
</tr>
<tr id="row1603881184093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870128074093521"><a name="p870128074093521"></a><a name="p870128074093521"></a><a href="spimsg.md">SpiMsg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p65176484093521"><a name="p65176484093521"></a><a name="p65176484093521"></a>Defines the custom SPI transfer message. </p>
</td>
</tr>
<tr id="row1257319220093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1403817877093521"><a name="p1403817877093521"></a><a name="p1403817877093521"></a><a href="spicfg.md">SpiCfg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913295415093521"><a name="p1913295415093521"></a><a name="p1913295415093521"></a>Defines the configuration of an SPI device. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table335845954093521"></a>
<table><thead align="left"><tr id="row558238895093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1214294220093521"><a name="p1214294220093521"></a><a name="p1214294220093521"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1341288115093521"><a name="p1341288115093521"></a><a name="p1341288115093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row25969202093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p323664500093521"><a name="p323664500093521"></a><a name="p323664500093521"></a><a href="spi.md#ga430ad9ccffd42f4427ba22fcc8167c64">SPI_CLK_PHASE</a>   (1 &lt;&lt; 0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p434607306093521"><a name="p434607306093521"></a><a name="p434607306093521"></a>Indicates the SPI clock phase. The value <strong id="b376647140093521"><a name="b376647140093521"></a><a name="b376647140093521"></a>0</strong> indicates that data will be sampled on the first clock edge, and <strong id="b148985592093521"><a name="b148985592093521"></a><a name="b148985592093521"></a>1</strong> indicates that data will be sampled on the second clock edge. </p>
</td>
</tr>
<tr id="row107564379093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292217180093521"><a name="p292217180093521"></a><a name="p292217180093521"></a><a href="spi.md#ga4cafe948918622f80c27db640c6c23c6">SPI_CLK_POLARITY</a>   (1 &lt;&lt; 1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924887278093521"><a name="p924887278093521"></a><a name="p924887278093521"></a>Indicates the SPI clock polarity. The value <strong id="b564099346093521"><a name="b564099346093521"></a><a name="b564099346093521"></a>0</strong> indicates a low-level clock signal in the idle state, and <strong id="b230096966093521"><a name="b230096966093521"></a><a name="b230096966093521"></a>1</strong> indicates a high-level clock signal in the idle state. </p>
</td>
</tr>
<tr id="row1211187689093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146564051093521"><a name="p2146564051093521"></a><a name="p2146564051093521"></a><a href="spi.md#ga11113e647ddd2101c1c693632f63aa7c">SPI_MODE_3WIRE</a>   (1 &lt;&lt; 2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p599309924093521"><a name="p599309924093521"></a><a name="p599309924093521"></a>Indicates that a single data line is used for both input and output. </p>
</td>
</tr>
<tr id="row2102523282093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1957541920093521"><a name="p1957541920093521"></a><a name="p1957541920093521"></a><a href="spi.md#ga8619b297de563eca6852af34c79daa62">SPI_MODE_LOOP</a>   (1 &lt;&lt; 3)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786485675093521"><a name="p786485675093521"></a><a name="p786485675093521"></a>Indicates the SPI loopback mode. </p>
</td>
</tr>
<tr id="row667241970093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p591853316093521"><a name="p591853316093521"></a><a name="p591853316093521"></a><a href="spi.md#ga4da8777b0d2d7dd96d6038411791c36e">SPI_MODE_LSBFE</a>   (1 &lt;&lt; 4)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p657889638093521"><a name="p657889638093521"></a><a name="p657889638093521"></a>Indicates the SPI data transfer order. The value <strong id="b659843167093521"><a name="b659843167093521"></a><a name="b659843167093521"></a>0</strong> indicates that data is transferred from the most significant bit (MSB) to the least significant bit (LSB), and <strong id="b1830599028093521"><a name="b1830599028093521"></a><a name="b1830599028093521"></a>1</strong> indicates the opposite. </p>
</td>
</tr>
<tr id="row144185880093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p415345044093521"><a name="p415345044093521"></a><a name="p415345044093521"></a><a href="spi.md#ga361195644b8e753d5469dd492c66217b">SPI_MODE_NOCS</a>   (1 &lt;&lt; 5)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033314316093521"><a name="p2033314316093521"></a><a name="p2033314316093521"></a>Indicates that there is only one SPI device, and no chip select (CS) is required. </p>
</td>
</tr>
<tr id="row1168189513093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p990753061093521"><a name="p990753061093521"></a><a name="p990753061093521"></a><a href="spi.md#ga33d89d81eb33b7a5de1a03e88279163d">SPI_MODE_CS_HIGH</a>   (1 &lt;&lt; 6)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688748400093521"><a name="p1688748400093521"></a><a name="p1688748400093521"></a>Indicates that the CS level is high when an SPI device is selected. </p>
</td>
</tr>
<tr id="row1011753813093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2005910580093521"><a name="p2005910580093521"></a><a name="p2005910580093521"></a><a href="spi.md#ga42f3ef9ad5429ac10662448fe1f5a746">SPI_MODE_READY</a>   (1 &lt;&lt; 7)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1195358890093521"><a name="p1195358890093521"></a><a name="p1195358890093521"></a>Indicates that the SPI device is set to low for pausing data transfer. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1476117983093521"></a>
<table><thead align="left"><tr id="row256004643093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1899224769093521"><a name="p1899224769093521"></a><a name="p1899224769093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1447184106093521"><a name="p1447184106093521"></a><a name="p1447184106093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1356220970093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1863174034093521"><a name="p1863174034093521"></a><a name="p1863174034093521"></a><a href="spi.md#ga55946d1d895fc2b7b33007019de1668f">SpiTransferMode</a> { <a href="spi.md#gga55946d1d895fc2b7b33007019de1668fad91925d3e1b3e82ff14004dd0b9d98a3">SPI_INTERRUPT_TRANSFER</a> = 0, <a href="spi.md#gga55946d1d895fc2b7b33007019de1668fa51d9bac6c8cbf4d95705563b097bb0b2">SPI_POLLING_TRANSFER</a>, <a href="spi.md#gga55946d1d895fc2b7b33007019de1668fad4d2e8d82f1d9a15198399d6540bacd1">SPI_DMA_TRANSFER</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424566176093521"><a name="p1424566176093521"></a><a name="p1424566176093521"></a>Enumerates transfer modes of SPI data. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1346892950093521"></a>
<table><thead align="left"><tr id="row1057043327093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1490303513093521"><a name="p1490303513093521"></a><a name="p1490303513093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p265862611093521"><a name="p265862611093521"></a><a name="p265862611093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row571923097093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p876966305093521"><a name="p876966305093521"></a><a name="p876966305093521"></a><a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a> (const struct <a href="spidevinfo.md">SpiDevInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1682823309093521"><a name="p1682823309093521"></a><a name="p1682823309093521"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1724341027093521"><a name="p1724341027093521"></a><a name="p1724341027093521"></a>Obtains the handle of an SPI device. </p>
</td>
</tr>
<tr id="row1730686649093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p679681923093521"><a name="p679681923093521"></a><a name="p679681923093521"></a><a href="spi.md#gad5b082d6d0699a9bc5240d6a5491f08a">SpiClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533677590093521"><a name="p1533677590093521"></a><a name="p1533677590093521"></a>void </p>
<p id="p1651660442093521"><a name="p1651660442093521"></a><a name="p1651660442093521"></a>Releases the handle of an SPI device. </p>
</td>
</tr>
<tr id="row1575128146093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437776492093521"><a name="p1437776492093521"></a><a name="p1437776492093521"></a><a href="spi.md#ga40e7274a4291f1482e720c956a291e9f">SpiTransfer</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="spimsg.md">SpiMsg</a> *msgs, uint32_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1854945904093521"><a name="p1854945904093521"></a><a name="p1854945904093521"></a>int32_t </p>
<p id="p1417616247093521"><a name="p1417616247093521"></a><a name="p1417616247093521"></a>Launches a custom transfer to an SPI device. </p>
</td>
</tr>
<tr id="row694095350093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1915010039093521"><a name="p1915010039093521"></a><a name="p1915010039093521"></a><a href="spi.md#gad7c852b1c6aed4380e393637aeb66802">SpiRead</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *buf, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2079029403093521"><a name="p2079029403093521"></a><a name="p2079029403093521"></a>int32_t </p>
<p id="p34931560093521"><a name="p34931560093521"></a><a name="p34931560093521"></a>Reads data of a specified length from an SPI device. </p>
</td>
</tr>
<tr id="row826964375093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2030996491093521"><a name="p2030996491093521"></a><a name="p2030996491093521"></a><a href="spi.md#ga77314bd5d40f78d97b25048b2e816ff9">SpiWrite</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *buf, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2113890420093521"><a name="p2113890420093521"></a><a name="p2113890420093521"></a>int32_t </p>
<p id="p1517945831093521"><a name="p1517945831093521"></a><a name="p1517945831093521"></a>Writes data of a specified length to an SPI device. </p>
</td>
</tr>
<tr id="row1246394340093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p585380539093521"><a name="p585380539093521"></a><a name="p585380539093521"></a><a href="spi.md#ga0d8781e50042c5d89733d21097bec359">SpiSetCfg</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="spicfg.md">SpiCfg</a> *cfg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159346474093521"><a name="p159346474093521"></a><a name="p159346474093521"></a>int32_t </p>
<p id="p93991276093521"><a name="p93991276093521"></a><a name="p93991276093521"></a>Sets configuration parameters for an SPI device. </p>
</td>
</tr>
<tr id="row890471965093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2123119572093521"><a name="p2123119572093521"></a><a name="p2123119572093521"></a><a href="spi.md#gabd835b51efecc8364c8b61914466d172">SpiGetCfg</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="spicfg.md">SpiCfg</a> *cfg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146571188093521"><a name="p1146571188093521"></a><a name="p1146571188093521"></a>int32_t </p>
<p id="p494787072093521"><a name="p494787072093521"></a><a name="p494787072093521"></a>Obtains the configuration parameters of an SPI device. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1389692829093521"></a>

## **Macro Definition Documentation**<a name="section330531134093521"></a>

## SPI\_CLK\_PHASE<a name="ga430ad9ccffd42f4427ba22fcc8167c64"></a>

```
#define SPI_CLK_PHASE   (1 << 0)
```

 **Description:**

Indicates the SPI clock phase. The value  **0**  indicates that data will be sampled on the first clock edge, and  **1**  indicates that data will be sampled on the second clock edge. 

## SPI\_CLK\_POLARITY<a name="ga4cafe948918622f80c27db640c6c23c6"></a>

```
#define SPI_CLK_POLARITY   (1 << 1)
```

 **Description:**

Indicates the SPI clock polarity. The value  **0**  indicates a low-level clock signal in the idle state, and  **1**  indicates a high-level clock signal in the idle state. 

## SPI\_MODE\_3WIRE<a name="ga11113e647ddd2101c1c693632f63aa7c"></a>

```
#define SPI_MODE_3WIRE   (1 << 2)
```

 **Description:**

Indicates that a single data line is used for both input and output. 

## SPI\_MODE\_CS\_HIGH<a name="ga33d89d81eb33b7a5de1a03e88279163d"></a>

```
#define SPI_MODE_CS_HIGH   (1 << 6)
```

 **Description:**

Indicates that the CS level is high when an SPI device is selected. 

## SPI\_MODE\_LOOP<a name="ga8619b297de563eca6852af34c79daa62"></a>

```
#define SPI_MODE_LOOP   (1 << 3)
```

 **Description:**

Indicates the SPI loopback mode. 

## SPI\_MODE\_LSBFE<a name="ga4da8777b0d2d7dd96d6038411791c36e"></a>

```
#define SPI_MODE_LSBFE   (1 << 4)
```

 **Description:**

Indicates the SPI data transfer order. The value  **0**  indicates that data is transferred from the most significant bit \(MSB\) to the least significant bit \(LSB\), and  **1**  indicates the opposite. 

## SPI\_MODE\_NOCS<a name="ga361195644b8e753d5469dd492c66217b"></a>

```
#define SPI_MODE_NOCS   (1 << 5)
```

 **Description:**

Indicates that there is only one SPI device, and no chip select \(CS\) is required. 

## SPI\_MODE\_READY<a name="ga42f3ef9ad5429ac10662448fe1f5a746"></a>

```
#define SPI_MODE_READY   (1 << 7)
```

 **Description:**

Indicates that the SPI device is set to low for pausing data transfer. 

## **Enumeration Type Documentation**<a name="section830931801093521"></a>

## SpiTransferMode<a name="ga55946d1d895fc2b7b33007019de1668f"></a>

```
enum [SpiTransferMode](spi.md#ga55946d1d895fc2b7b33007019de1668f)
```

 **Description:**

Enumerates transfer modes of SPI data. 

**Attention:**

The specific SPI controller determines which variables in this structure are supported.


<a name="table1624878936093521"></a>
<table><thead align="left"><tr id="row733783370093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1335312882093521"><a name="p1335312882093521"></a><a name="p1335312882093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1458815782093521"><a name="p1458815782093521"></a><a name="p1458815782093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row784090506093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga55946d1d895fc2b7b33007019de1668fad91925d3e1b3e82ff14004dd0b9d98a3"><a name="gga55946d1d895fc2b7b33007019de1668fad91925d3e1b3e82ff14004dd0b9d98a3"></a><a name="gga55946d1d895fc2b7b33007019de1668fad91925d3e1b3e82ff14004dd0b9d98a3"></a></strong>SPI_INTERRUPT_TRANSFER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445753727093521"><a name="p1445753727093521"></a><a name="p1445753727093521"></a>Interrupt transfer mode </p>
 </td>
</tr>
<tr id="row1136191175093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga55946d1d895fc2b7b33007019de1668fa51d9bac6c8cbf4d95705563b097bb0b2"><a name="gga55946d1d895fc2b7b33007019de1668fa51d9bac6c8cbf4d95705563b097bb0b2"></a><a name="gga55946d1d895fc2b7b33007019de1668fa51d9bac6c8cbf4d95705563b097bb0b2"></a></strong>SPI_POLLING_TRANSFER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1043940948093521"><a name="p1043940948093521"></a><a name="p1043940948093521"></a>Polling transfer mode </p>
 </td>
</tr>
<tr id="row88084506093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga55946d1d895fc2b7b33007019de1668fad4d2e8d82f1d9a15198399d6540bacd1"><a name="gga55946d1d895fc2b7b33007019de1668fad4d2e8d82f1d9a15198399d6540bacd1"></a><a name="gga55946d1d895fc2b7b33007019de1668fad4d2e8d82f1d9a15198399d6540bacd1"></a></strong>SPI_DMA_TRANSFER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550440752093521"><a name="p1550440752093521"></a><a name="p1550440752093521"></a>Direct Memory Access (DMA) transfer mode </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1373272476093521"></a>

## SpiClose\(\)<a name="gad5b082d6d0699a9bc5240d6a5491f08a"></a>

```
void SpiClose (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Releases the handle of an SPI device. 

**Parameters:**

<a name="table1932028991093521"></a>
<table><thead align="left"><tr id="row1386553696093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1244209033093521"><a name="p1244209033093521"></a><a name="p1244209033093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1248658544093521"><a name="p1248658544093521"></a><a name="p1248658544093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row523506989093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device handle obtained via <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>.</td>
</tr>
</tbody>
</table>

## SpiGetCfg\(\)<a name="gabd835b51efecc8364c8b61914466d172"></a>

```
int32_t SpiGetCfg (struct [DevHandle](devhandle.md) * handle, struct [SpiCfg](spicfg.md) * cfg )
```

 **Description:**

Obtains the configuration parameters of an SPI device. 

**Parameters:**

<a name="table2088559337093521"></a>
<table><thead align="left"><tr id="row1756647455093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p477239580093521"><a name="p477239580093521"></a><a name="p477239580093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p490894048093521"><a name="p490894048093521"></a><a name="p490894048093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row789553538093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device handle obtained via <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </td>
</tr>
<tr id="row23223691093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cfg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration parameters.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## SpiOpen\(\)<a name="ga073b44f262ca3b99fa632a1468bc1190"></a>

```
struct [DevHandle](devhandle.md)* SpiOpen (const struct [SpiDevInfo](spidevinfo.md) * info)
```

 **Description:**

Obtains the handle of an SPI device. 

**Parameters:**

<a name="table183012169093521"></a>
<table><thead align="left"><tr id="row1254385303093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1055151799093521"><a name="p1055151799093521"></a><a name="p1055151799093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1443218514093521"><a name="p1443218514093521"></a><a name="p1443218514093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1790595143093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device information.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the handle of the SPI device if the operation is successful; returns  **NULL**  otherwise.



## SpiRead\(\)<a name="gad7c852b1c6aed4380e393637aeb66802"></a>

```
int32_t SpiRead (struct [DevHandle](devhandle.md) * handle, uint8_t * buf, uint32_t len )
```

 **Description:**

Reads data of a specified length from an SPI device. 

**Parameters:**

<a name="table1920314295093521"></a>
<table><thead align="left"><tr id="row468473702093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p618741833093521"><a name="p618741833093521"></a><a name="p618741833093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1061312265093521"><a name="p1061312265093521"></a><a name="p1061312265093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row423561892093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device handle obtained via <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </td>
</tr>
<tr id="row726048780093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for receiving the data. </td>
</tr>
<tr id="row1002855703093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to read.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## SpiSetCfg\(\)<a name="ga0d8781e50042c5d89733d21097bec359"></a>

```
int32_t SpiSetCfg (struct [DevHandle](devhandle.md) * handle, struct [SpiCfg](spicfg.md) * cfg )
```

 **Description:**

Sets configuration parameters for an SPI device. 

**Parameters:**

<a name="table1148947538093521"></a>
<table><thead align="left"><tr id="row1273019704093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p469736465093521"><a name="p469736465093521"></a><a name="p469736465093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p245526202093521"><a name="p245526202093521"></a><a name="p245526202093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row484824111093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device handle obtained via <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </td>
</tr>
<tr id="row282679029093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cfg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration parameters.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



## SpiTransfer\(\)<a name="ga40e7274a4291f1482e720c956a291e9f"></a>

```
int32_t SpiTransfer (struct [DevHandle](devhandle.md) * handle, struct [SpiMsg](spimsg.md) * msgs, uint32_t count )
```

 **Description:**

Launches a custom transfer to an SPI device. 

**Parameters:**

<a name="table1478364244093521"></a>
<table><thead align="left"><tr id="row1757939666093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1831031926093521"><a name="p1831031926093521"></a><a name="p1831031926093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p808152174093521"><a name="p808152174093521"></a><a name="p808152174093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row480462019093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device handle obtained via <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </td>
</tr>
<tr id="row1604466317093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">msgs</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to transfer. </td>
</tr>
<tr id="row1029134741093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">count</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the message structure array.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 

**See also:**

[SpiMsg](spimsg.md) 

## SpiWrite\(\)<a name="ga77314bd5d40f78d97b25048b2e816ff9"></a>

```
int32_t SpiWrite (struct [DevHandle](devhandle.md) * handle, uint8_t * buf, uint32_t len )
```

 **Description:**

Writes data of a specified length to an SPI device. 

**Parameters:**

<a name="table141123104093521"></a>
<table><thead align="left"><tr id="row1975240830093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p321836971093521"><a name="p321836971093521"></a><a name="p321836971093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1467184158093521"><a name="p1467184158093521"></a><a name="p1467184158093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row124677265093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the SPI device handle obtained via <a href="spi.md#ga073b44f262ca3b99fa632a1468bc1190">SpiOpen</a>. </td>
</tr>
<tr id="row1765608993093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to write. </td>
</tr>
<tr id="row991123733093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to write.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise.



