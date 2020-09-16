# ntpdate<a name="EN-US_TOPIC_0000001052170282"></a>

## Command Function<a name="section38494293815"></a>

This command is used to synchronize system time from the server.

## Syntax<a name="section5503114413387"></a>

ntpdate \[_SERVER\_IP1_\] \[_SERVER\_IP2_\]...

## Parameter Description<a name="section136934472383"></a>

**Table  1**  Parameters

<a name="table2616mcpsimp"></a>
<table><thead align="left"><tr id="row2622mcpsimp"><th class="cellrowborder" valign="top" width="20.79%" id="mcps1.2.4.1.1"><p id="p2624mcpsimp"><a name="p2624mcpsimp"></a><a name="p2624mcpsimp"></a><strong id="b156978804711722"><a name="b156978804711722"></a><a name="b156978804711722"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52.480000000000004%" id="mcps1.2.4.1.2"><p id="p2626mcpsimp"><a name="p2626mcpsimp"></a><a name="p2626mcpsimp"></a><strong id="b53501572310"><a name="b53501572310"></a><a name="b53501572310"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="26.729999999999997%" id="mcps1.2.4.1.3"><p id="p2628mcpsimp"><a name="p2628mcpsimp"></a><a name="p2628mcpsimp"></a><strong id="b88462564511722"><a name="b88462564511722"></a><a name="b88462564511722"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row2629mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2631mcpsimp"><a name="p2631mcpsimp"></a><a name="p2631mcpsimp"></a>SERVER_IP</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2633mcpsimp"><a name="p2633mcpsimp"></a><a name="p2633mcpsimp"></a>Indicates the IP address of the NTP server.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2634mcpsimpp0"><a name="entry2634mcpsimpp0"></a><a name="entry2634mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section121401651173816"></a>

Run the  **ntpdate **\[_SERVER\_IP1_\] \[_SERVER\_IP2_\]... command.  **ntpdate**  obtains and displays the time of the first server with a valid IP address.

## Example<a name="section3431554203811"></a>

To update the system time, run  **ntpdate 192.168.1.3**.

## Output<a name="section18638194610115"></a>

```
OHOS # ntpdate 192.168.1.3
time server 192.168.1.3: Mon Jun 13 09:24:25 2016
```

The time zone of the board is different from that of the server. Therefore, the displayed time may be several hours different from the obtained server time.

