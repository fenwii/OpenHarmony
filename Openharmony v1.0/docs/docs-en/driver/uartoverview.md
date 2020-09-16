# UART Overview<a name="EN-US_TOPIC_0000001052215244"></a>

## Introduction<a name="section14770623164917"></a>

-   The Universal Asynchronous Receiver/Transmitter \(UART\) is a universal serial data bus used for asynchronous communication. It enables bi-directional communication between devices in full-duplex mode.
-   UART is widely used to print information for debugging or to connect to various external modules such as GPS and Bluetooth.
-   A UART is connected to other modules through two wires \(as shown in  [Figure 1](#fig209936401896)\) or four wires \(as shown in  [Figure 2](#fig1435614171015)\).
    1.  TX: TX pin of the transmitting UART. It is connected to the RX pin of the peer UART.
    2.  RX: RX pin of the receiving UART. It is connected to the TX pin of the peer UART.
    3.  RTS: Request to Send signal pin. It is connected to the CTS pin of the peer UART and is used to indicate whether the local UART is ready to receive data.
    4.  CTS: Clear to Send signal pin. It is connected to the RTS pin of the peer UART and is used to indicate whether the local UART is allowed to send data to the peer end.

        **Figure  1**  2-wire UART communication<a name="fig209936401896"></a>  
        

        ![](figures/en-us_image_0000001053926237.png)

        **Figure  2**  4-wire UART communication<a name="fig1435614171015"></a>  
        

        ![](figures/en-us_image_0000001054007499.png)


-   The transmitting and receiving UARTs must ensure that they have the same settings on particular attributes such as the baud rate and data format \(start bit, data bit, parity bit, and stop bit\) before they start to communicate. During data transmission, a UART sends data to the peer end over the TX pin and receives data from the peer end over the RX pin. When the size of the buffer used by a UART for storing received data reaches the preset threshold, the RTS signal of the UART changes to  **1**  \(data cannot be received\), and the peer UART stops sending data to it because its CTS signal does not allow it to send data.
-   The UART interface defines a set of common functions for operating a UART port, including obtaining and releasing device handles, reading and writing data of a specified length, and obtaining and setting the baud rate, as well as the device attributes.

## Available APIs<a name="section149505462492"></a>

**Table  1**  APIs for the UART driver

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row1223152681611"><th class="cellrowborder" valign="top" width="26.619999999999997%" id="mcps1.2.4.1.1"><p id="p210413571619"><a name="p210413571619"></a><a name="p210413571619"></a><strong id="b4100105545211"><a name="b4100105545211"></a><a name="b4100105545211"></a>Capability</strong></p>
</th>
<th class="cellrowborder" valign="top" width="31.369999999999997%" id="mcps1.2.4.1.2"><p id="p810403511614"><a name="p810403511614"></a><a name="p810403511614"></a><strong id="b1653121711186"><a name="b1653121711186"></a><a name="b1653121711186"></a>Function</strong></p>
</th>
<th class="cellrowborder" valign="top" width="42.01%" id="mcps1.2.4.1.3"><p id="p110418354161"><a name="p110418354161"></a><a name="p110418354161"></a><strong id="b69108168153412"><a name="b69108168153412"></a><a name="b69108168153412"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1638573613415"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p917154316414"><a name="p917154316414"></a><a name="p917154316414"></a>Obtaining and releasing device handles</p>
<p id="p9596111154212"><a name="p9596111154212"></a><a name="p9596111154212"></a></p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p20385163614412"><a name="p20385163614412"></a><a name="p20385163614412"></a>UartOpen</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p12101135184213"><a name="p12101135184213"></a><a name="p12101135184213"></a>Obtains the UART device handle.</p>
</td>
</tr>
<tr id="row5950143316415"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p149501733134113"><a name="p149501733134113"></a><a name="p149501733134113"></a>UartClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p371073520422"><a name="p371073520422"></a><a name="p371073520422"></a>Releases a specified UART device handle.</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>Reading and writing data</p>
<p id="p131072201215"><a name="p131072201215"></a><a name="p131072201215"></a></p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p8296182221219"><a name="p8296182221219"></a><a name="p8296182221219"></a>UartRead</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p16297172213125"><a name="p16297172213125"></a><a name="p16297172213125"></a>Reads data of a specified length from a UART device.</p>
</td>
</tr>
<tr id="row11585016539"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1095722493616"><a name="p1095722493616"></a><a name="p1095722493616"></a>UartWrite</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p15297162215122"><a name="p15297162215122"></a><a name="p15297162215122"></a>Writes data of a specified length into a UART device.</p>
</td>
</tr>
<tr id="row8687115843715"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p196317143813"><a name="p196317143813"></a><a name="p196317143813"></a>Obtaining and setting the baud rate</p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p166885582375"><a name="p166885582375"></a><a name="p166885582375"></a>UartGetBaud</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p13688358183716"><a name="p13688358183716"></a><a name="p13688358183716"></a>Obtains the UART baud rate.</p>
</td>
</tr>
<tr id="row18987529382"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p698719214383"><a name="p698719214383"></a><a name="p698719214383"></a>UartSetBaud</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1398712123810"><a name="p1398712123810"></a><a name="p1398712123810"></a>Sets the UART baud rate.</p>
</td>
</tr>
<tr id="row1551850115317"><td class="cellrowborder" rowspan="2" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p1629782201218"><a name="p1629782201218"></a><a name="p1629782201218"></a>Obtaining and setting device attributes</p>
<p id="p10308192211216"><a name="p10308192211216"></a><a name="p10308192211216"></a></p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p32972022151218"><a name="p32972022151218"></a><a name="p32972022151218"></a>UartGetAttribute</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p13297122216123"><a name="p13297122216123"></a><a name="p13297122216123"></a>Obtains the UART device attributes.</p>
</td>
</tr>
<tr id="row7545065311"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p102974224120"><a name="p102974224120"></a><a name="p102974224120"></a>UartSetAttribute</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p152971322111219"><a name="p152971322111219"></a><a name="p152971322111219"></a>Sets the UART device attributes.</p>
</td>
</tr>
<tr id="row14614115403"><td class="cellrowborder" valign="top" width="26.619999999999997%" headers="mcps1.2.4.1.1 "><p id="p1746281144010"><a name="p1746281144010"></a><a name="p1746281144010"></a>Setting the transmission mode</p>
</td>
<td class="cellrowborder" valign="top" width="31.369999999999997%" headers="mcps1.2.4.1.2 "><p id="p1146215112405"><a name="p1146215112405"></a><a name="p1146215112405"></a>UartSetTransMode</p>
</td>
<td class="cellrowborder" valign="top" width="42.01%" headers="mcps1.2.4.1.3 "><p id="p11303181216414"><a name="p11303181216414"></a><a name="p11303181216414"></a>Sets the UART transmission mode.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel space.

