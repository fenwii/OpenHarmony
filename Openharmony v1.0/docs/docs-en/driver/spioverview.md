# SPI Overview<a name="EN-US_TOPIC_0000001053057951"></a>

## Introduction<a name="section9202632114011"></a>

-   Serial Peripheral Interface \(SPI\) is a serial bus specification used for high-speed, full-duplex, and synchronous communication.
-   SPI is developed by Motorola. It is commonly used for communication with flash memory, real-time clocks, sensors, and analog-to-digital \(A/D\) converters.
-   SPI works in controller/device mode. Generally, there is one SPI controller that controls one or more SPI devices. They are connected via four wires:
    -   SCLK: clock signals output from the SPI controller
    -   MOSI: data output from the SPI controller and input into a SPI device
    -   MISO: data output from a SPI device and input into the SPI controller
    -   CS: signals enabled by a SPI device and controlled by the SPI controller


-   [Figure 1](#fig15227181812587)  shows the connection between one SPI controller and two SPI devices \(Device A and Device B\). In this figure, Device A and Device B share three pins \(SCLK, MISO, and MOSI\) of the controller. CS0 of Device A and CS1 of Device B are connected to CS0 and CS1 of the controller, respectively.

**Figure  1**  SPI controller/device connection<a name="fig15227181812587"></a>  


![](figures/en-us_image_0000001054142582.png)

-   SPI communication is usually initiated by a controller and is operated as follows:

1.  A single SPI device is selected at a time via the CS to communicate with the SPI controller.
2.  Clock signals are provided for the selected SPI device via the SCLK.
3.  SPI controller sends data to SPI devices via the MOSI, and receives data from SPI devices via the MISO.

-   SPI can work in one of the following four modes, equivalent to one of the four possible states for Clock Polarity \(CPOL\) and Clock Phase \(CPHA\):
    -   When both CPOL and CPHA are  **0**, the clock signal level is low in the idle state and data is sampled on the first clock edge.
    -   When CPOL is  **0**  and CPHA is  **1**, the clock signal level is low in the idle state and data is sampled on the second clock edge.
    -   When CPOL is  **1**  and CPHA is  **0**, the clock signal level is high in the idle state and data is sampled on the first clock edge.
    -   When both CPOL and CPHA are  **1**, the clock signal level is high in the idle state and data is sampled on the second clock edge.


-   SPI defines a set of common functions for operating an SPI device, including those for:
    -   Obtaining and releasing the handle of an SPI device.
    -   Reading or writing data of a specified length from or into an SPI device.
    -   Customizing data reading or writing via  **SpiMsg**.
    -   Obtaining and setting SPI device configuration parameters.


>![](public_sys-resources/icon-note.gif) **NOTE:** 
>Currently, these functions are only applicable in the communication initiated by the SPI controller.

## Available APIs<a name="section1859594134119"></a>

**Table  1**  APIs for the SPI driver

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" align="left" valign="top" width="20.857914208579142%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a><strong id="b17365506414"><a name="b17365506414"></a><a name="b17365506414"></a>Capability</strong></p>
</th>
<th class="cellrowborder" align="left" valign="top" width="23.36766323367663%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a><strong id="b191701618154210"><a name="b191701618154210"></a><a name="b191701618154210"></a>Function</strong></p>
</th>
<th class="cellrowborder" align="left" valign="top" width="55.77442255774422%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a><strong id="b64281840104214"><a name="b64281840104214"></a><a name="b64281840104214"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1651292212306"><td class="cellrowborder" rowspan="2" valign="top" width="20.857914208579142%" headers="mcps1.2.4.1.1 "><p id="p1387414255305"><a name="p1387414255305"></a><a name="p1387414255305"></a>SPI device handle obtaining/releasing</p>
</td>
<td class="cellrowborder" valign="top" width="23.36766323367663%" headers="mcps1.2.4.1.2 "><p id="p8874825143014"><a name="p8874825143014"></a><a name="p8874825143014"></a>SpiOpen</p>
</td>
<td class="cellrowborder" valign="top" width="55.77442255774422%" headers="mcps1.2.4.1.3 "><p id="p1087432513307"><a name="p1087432513307"></a><a name="p1087432513307"></a>Obtains an SPI device handle.</p>
</td>
</tr>
<tr id="row1429083612305"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1956614106311"><a name="p1956614106311"></a><a name="p1956614106311"></a>SpiClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p829111362306"><a name="p829111362306"></a><a name="p829111362306"></a>Releases an SPI device handle.</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="3" valign="top" width="20.857914208579142%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>SPI reading/writing</p>
</td>
<td class="cellrowborder" valign="top" width="23.36766323367663%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>SpiRead</p>
</td>
<td class="cellrowborder" valign="top" width="55.77442255774422%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>Reads data of a specified length from an SPI device.</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>SpiWrite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p573815197171"><a name="p573815197171"></a><a name="p573815197171"></a>Writes data of a specified length into an SPI device.</p>
</td>
</tr>
<tr id="row1766145611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p183904373018"><a name="p183904373018"></a><a name="p183904373018"></a>SpiTransfer</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1639011313303"><a name="p1639011313303"></a><a name="p1639011313303"></a>Transfers SPI data.</p>
</td>
</tr>
<tr id="row1020919129159"><td class="cellrowborder" rowspan="2" valign="top" width="20.857914208579142%" headers="mcps1.2.4.1.1 "><p id="p82092126154"><a name="p82092126154"></a><a name="p82092126154"></a>SPI device configuration</p>
<p id="p6794153701111"><a name="p6794153701111"></a><a name="p6794153701111"></a></p>
</td>
<td class="cellrowborder" valign="top" width="23.36766323367663%" headers="mcps1.2.4.1.2 "><p id="p1739013012154"><a name="p1739013012154"></a><a name="p1739013012154"></a>SpiSetCfg</p>
</td>
<td class="cellrowborder" valign="top" width="55.77442255774422%" headers="mcps1.2.4.1.3 "><p id="p073910197173"><a name="p073910197173"></a><a name="p073910197173"></a>Sets configuration parameters for an SPI device.</p>
</td>
</tr>
<tr id="row379443710118"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p4333154919111"><a name="p4333154919111"></a><a name="p4333154919111"></a>SpiGetCfg</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p11333649171117"><a name="p11333649171117"></a><a name="p11333649171117"></a>Obtains configuration parameters of an SPI device.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel space.

