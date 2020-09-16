# SDIO Overview<a name="EN-US_TOPIC_0000001053055057"></a>

## Introduction<a name="section1155271783811"></a>

-   Secure Digital Input/Output \(SDIO\) is a peripheral interface evolved from the Secure Digital \(SD\) memory card interface. The SDIO interface is compatible with SD memory cards and can be connected to devices that support the SDIO interface.
-   SDIO is widely used. Currently, many smartphones support SDIO, and many SDIO peripherals are developed for connections to smartphones. Common SDIO peripherals include WLAN, GPS, cameras, and Bluetooth.
-   The SDIO bus has two ends, named host and device. All communication starts when the host sends a command. The device can communicate with the host as long as it can parse the command of the host. An SDIO host can connect to multiple devices, as shown in the figure below.

    1.  CLK signal: clock signal sent from the host to the device
    2.  VDD signal: power signal
    3.  VSS signal: ground signal
    4.  D0-3 signal: four data lines. The DAT1 signal cable is multiplexed as the interrupt line. In 1-bit mode, DAT0 is used to transmit data. In 4-bit mode, DAT0 to DAT3 are used to transmit data.
    5.  CMD signal: used by the host to send commands and the device to respond to commands.

    **Figure  1**  Connections between the host and devices in SDIO<a name="fig1185316527498"></a>  
    

    ![](figures/en-us_image_0000001054280608.png)

-   The SDIO interface defines a set of common methods for operating an SDIO device, including opening and closing an SDIO controller, exclusively claiming and releasing the host, enabling and disabling devices, claiming and releasing an SDIO IRQ, reading and writing data based on SDIO, and obtaining and setting common information.

## Available APIs<a name="section10204143763819"></a>

**Table  1**  APIs available for the SDIO driver

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row1625342317507"><th class="cellrowborder" valign="top" width="21.07%" id="mcps1.2.4.1.1"><p id="p1779183435016"><a name="p1779183435016"></a><a name="p1779183435016"></a>Capability</p>
</th>
<th class="cellrowborder" valign="top" width="34.04%" id="mcps1.2.4.1.2"><p id="p1879163417502"><a name="p1879163417502"></a><a name="p1879163417502"></a>Function</p>
</th>
<th class="cellrowborder" valign="top" width="44.89%" id="mcps1.2.4.1.3"><p id="p1379113410506"><a name="p1379113410506"></a><a name="p1379113410506"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1351945135614"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p146755118566"><a name="p146755118566"></a><a name="p146755118566"></a>SDIO device opening/closing</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p1151945185614"><a name="p1151945185614"></a><a name="p1151945185614"></a>SdioOpen</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p85110451565"><a name="p85110451565"></a><a name="p85110451565"></a>Opens an SDIO controller with a specified bus number.</p>
</td>
</tr>
<tr id="row1062610995616"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p136261793568"><a name="p136261793568"></a><a name="p136261793568"></a>SdioClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p062614919566"><a name="p062614919566"></a><a name="p062614919566"></a>Closes an SDIO controller.</p>
</td>
</tr>
<tr id="row337105133315"><td class="cellrowborder" rowspan="6" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p07631557153319"><a name="p07631557153319"></a><a name="p07631557153319"></a>SDIO reading/writing</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p34551320121416"><a name="p34551320121416"></a><a name="p34551320121416"></a>SdioReadBytes</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p748062291415"><a name="p748062291415"></a><a name="p748062291415"></a>Incrementally reads a given length of data from a specified SDIO address.</p>
</td>
</tr>
<tr id="row9317134301618"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p10345104001412"><a name="p10345104001412"></a><a name="p10345104001412"></a>SdioWriteBytes</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p113452040141418"><a name="p113452040141418"></a><a name="p113452040141418"></a>Incrementally writes a given length of data into a specified SDIO address.</p>
</td>
</tr>
<tr id="row131301734171616"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p713025410166"><a name="p713025410166"></a><a name="p713025410166"></a>SdioReadBytesFromFixedAddr</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14130165418168"><a name="p14130165418168"></a><a name="p14130165418168"></a>Reads a given length of data from a fixed SDIO address.</p>
</td>
</tr>
<tr id="row1434434011147"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1913013546161"><a name="p1913013546161"></a><a name="p1913013546161"></a>SdioWriteBytesToFixedAddr</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p111301954131614"><a name="p111301954131614"></a><a name="p111301954131614"></a>Writes a given length of data into a fixed SDIO address.</p>
</td>
</tr>
<tr id="row364393591410"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1851815711620"><a name="p1851815711620"></a><a name="p1851815711620"></a>SdioReadBytesFromFunc0</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p751875761611"><a name="p751875761611"></a><a name="p751875761611"></a>Reads a given length of data from the address space of SDIO function 0.</p>
</td>
</tr>
<tr id="row17455333175"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1645519318173"><a name="p1645519318173"></a><a name="p1645519318173"></a>SdioWriteBytesToFunc0</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p114552320176"><a name="p114552320176"></a><a name="p114552320176"></a>Writes a given length of data into the address space of SDIO function 0.</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>SDIO block size setting</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p74531720181413"><a name="p74531720181413"></a><a name="p74531720181413"></a>SdioSetBlockSize</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p247972241411"><a name="p247972241411"></a><a name="p247972241411"></a>Sets the block size.</p>
</td>
</tr>
<tr id="row778816813238"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p1578958142317"><a name="p1578958142317"></a><a name="p1578958142317"></a>SDIO common information retrieval/setting</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p378918842311"><a name="p378918842311"></a><a name="p378918842311"></a>SdioGetCommonInfo</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p1078919892313"><a name="p1078919892313"></a><a name="p1078919892313"></a>Obtains common information.</p>
</td>
</tr>
<tr id="row5667102342417"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2668623182411"><a name="p2668623182411"></a><a name="p2668623182411"></a>SdioSetCommonInfo</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p14668192362419"><a name="p14668192362419"></a><a name="p14668192362419"></a>Sets common information.</p>
</td>
</tr>
<tr id="row1165101111256"><td class="cellrowborder" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p8166161192511"><a name="p8166161192511"></a><a name="p8166161192511"></a>SDIO data flushing</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p121662112256"><a name="p121662112256"></a><a name="p121662112256"></a>SdioFlushData</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p171661711112519"><a name="p171661711112519"></a><a name="p171661711112519"></a>Flushes data.</p>
</td>
</tr>
<tr id="row17388101522515"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p53101413268"><a name="p53101413268"></a><a name="p53101413268"></a>SDIO host exclusively claiming or releasing</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p1638881562520"><a name="p1638881562520"></a><a name="p1638881562520"></a>SdioClaimHost</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p143881715152517"><a name="p143881715152517"></a><a name="p143881715152517"></a>Claims a host exclusively.</p>
</td>
</tr>
<tr id="row5352175517251"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p93537557259"><a name="p93537557259"></a><a name="p93537557259"></a>SdioReleaseHost</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1235355511254"><a name="p1235355511254"></a><a name="p1235355511254"></a>Releases the exclusively claimed host.</p>
</td>
</tr>
<tr id="row8759125415269"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p272143815359"><a name="p272143815359"></a><a name="p272143815359"></a>SDIO device enablement</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p6760195452615"><a name="p6760195452615"></a><a name="p6760195452615"></a>SdioEnableFunc</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p9760135417263"><a name="p9760135417263"></a><a name="p9760135417263"></a>Enables an SDIO device.</p>
</td>
</tr>
<tr id="row1166105762620"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p5662175782616"><a name="p5662175782616"></a><a name="p5662175782616"></a>SdioDisableFunc</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p3662135722618"><a name="p3662135722618"></a><a name="p3662135722618"></a>Disables an SDIO device.</p>
</td>
</tr>
<tr id="row12332331113517"><td class="cellrowborder" rowspan="2" valign="top" width="21.07%" headers="mcps1.2.4.1.1 "><p id="p188181849203614"><a name="p188181849203614"></a><a name="p188181849203614"></a>SDIO IRQ claiming/releasing</p>
</td>
<td class="cellrowborder" valign="top" width="34.04%" headers="mcps1.2.4.1.2 "><p id="p933383133517"><a name="p933383133517"></a><a name="p933383133517"></a>SdioClaimIrq</p>
</td>
<td class="cellrowborder" valign="top" width="44.89%" headers="mcps1.2.4.1.3 "><p id="p20333431203510"><a name="p20333431203510"></a><a name="p20333431203510"></a>Claims an SDIO IRQ.</p>
</td>
</tr>
<tr id="row173103413357"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2073123413515"><a name="p2073123413515"></a><a name="p2073123413515"></a>SdioReleaseIrq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1773634153518"><a name="p1773634153518"></a><a name="p1773634153518"></a>Releases an SDIO IRQ.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel mode.

