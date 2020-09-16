# I2C Overview<a name="EN-US_TOPIC_0000001052778273"></a>

## Introduction<a name="section5361140416"></a>

-   The Inter-Integrated Circuit \(I2C\) is a simple, bidirectional, and synchronous serial bus that uses merely two wires.
-   In an I2C communication, one controller communicates with one or more devices through the serial data line \(SDA\) and serial clock line \(SCL\), as shown in  [Figure 1](#fig1135561232714).

-   I2C data transfer must begin with a  **START**  condition and end with a  **STOP**  condition. Data is transmitted byte-by-byte from the most significant bit to the least significant bit.
-   Each I2C node is recognized by a unique address and can serve as either a controller or a device. When the controller needs to communicate with a device, it writes the device address to the bus through broadcast. A device matching this address sends a response to set up a data transfer channel.

-   The I2C APIs define a set of common functions for I2C data transfer, including:

    -   I2C controller management: opening or closing an I2C controller
    -   I2C message transfer: custom transfer by using a message array

    **Figure  1**  Physical connection diagram for I2C<a name="fig1135561232714"></a>  
    ![](figures/physical-connection-diagram-for-i2c.png "physical-connection-diagram-for-i2c")


## Available APIs<a name="section7606310210"></a>

**Table  1**  APIs available for the I2C driver

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="18.63%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a>Capability</p>
</th>
<th class="cellrowborder" valign="top" width="28.03%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="53.339999999999996%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="18.63%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>I2C controller management</p>
</td>
<td class="cellrowborder" valign="top" width="28.03%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>I2cOpen</p>
</td>
<td class="cellrowborder" valign="top" width="53.339999999999996%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>Opens an I2C controller.</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>I2cClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p573815197171"><a name="p573815197171"></a><a name="p573815197171"></a>Closes an I2C controller.</p>
</td>
</tr>
<tr id="row15108165391412"><td class="cellrowborder" valign="top" width="18.63%" headers="mcps1.2.4.1.1 "><p id="p91084533141"><a name="p91084533141"></a><a name="p91084533141"></a>I2C message transfer</p>
</td>
<td class="cellrowborder" valign="top" width="28.03%" headers="mcps1.2.4.1.2 "><p id="p13901730101511"><a name="p13901730101511"></a><a name="p13901730101511"></a>I2cTransfer</p>
</td>
<td class="cellrowborder" valign="top" width="53.339999999999996%" headers="mcps1.2.4.1.3 "><p id="p12738111912171"><a name="p12738111912171"></a><a name="p12738111912171"></a>Performs a custom transfer.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel mode.

