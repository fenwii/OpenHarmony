# netstat<a name="EN-US_TOPIC_0000001052370301"></a>

## Command Function<a name="section13469162113816"></a>

The  **netstat**  command is a console command and is used for monitoring the TCP/IP network. It can display the actual network connections and the status of each network interface device. It is used to display the statistics related to the TCP and UDP protocols and check the network connection to each port on the device \(board\).

## Syntax<a name="section795712373812"></a>

netstat

## Parameter Description<a name="section17629431193817"></a>

None

## Usage<a name="section5277153519380"></a>

Run the command directly.

## Example<a name="section108141437163820"></a>

Enter  **netstat**.

**Figure  1**  Output information<a name="fig51865585412"></a>  
![](figures/output-information.png "output-information")

## Output<a name="section1357015107117"></a>

**Table  1**  Output description

<a name="table2526mcpsimp"></a>
<table><thead align="left"><tr id="row2531mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p2533mcpsimp"><a name="p2533mcpsimp"></a><a name="p2533mcpsimp"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p2535mcpsimp"><a name="p2535mcpsimp"></a><a name="p2535mcpsimp"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2536mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2538mcpsimp"><a name="p2538mcpsimp"></a><a name="p2538mcpsimp"></a>Proto</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2540mcpsimp"><a name="p2540mcpsimp"></a><a name="p2540mcpsimp"></a>Indicates the protocol type.</p>
</td>
</tr>
<tr id="row2546mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2548mcpsimp"><a name="p2548mcpsimp"></a><a name="p2548mcpsimp"></a>Recv-Q</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2550mcpsimp"><a name="p2550mcpsimp"></a><a name="p2550mcpsimp"></a>Indicates the amount of data that is not read by the user.</p>
<p id="p2551mcpsimp"><a name="p2551mcpsimp"></a><a name="p2551mcpsimp"></a>For Listen TCP, the value indicates the number of TCP connections that have completed three-way handshake but are not accepted by users.</p>
</td>
</tr>
<tr id="row2553mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2555mcpsimp"><a name="p2555mcpsimp"></a><a name="p2555mcpsimp"></a>Send-Q</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1250715415473"><a name="p1250715415473"></a><a name="p1250715415473"></a>For a TCP connection, this value indicates the amount of data that has been sent but not acknowledged.</p>
<p id="p1080412214470"><a name="p1080412214470"></a><a name="p1080412214470"></a>For a UDP connection, this value indicates the amount of data buffered before IP address resolution is complete.</p>
</td>
</tr>
<tr id="row2558mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2560mcpsimp"><a name="p2560mcpsimp"></a><a name="p2560mcpsimp"></a>Local Address</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2562mcpsimp"><a name="p2562mcpsimp"></a><a name="p2562mcpsimp"></a>Indicates the local IP address and port number.</p>
</td>
</tr>
<tr id="row2563mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2565mcpsimp"><a name="p2565mcpsimp"></a><a name="p2565mcpsimp"></a>Foreign Address</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2567mcpsimp"><a name="p2567mcpsimp"></a><a name="p2567mcpsimp"></a>Indicates the remote IP address and port number.</p>
</td>
</tr>
<tr id="row2568mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p2570mcpsimp"><a name="p2570mcpsimp"></a><a name="p2570mcpsimp"></a>State</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p2572mcpsimp"><a name="p2572mcpsimp"></a><a name="p2572mcpsimp"></a>Indicates the TCP connection status. This parameter is meaningless for UDP.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>The command output like "========== total sockets 32 ====== unused sockets 22 BootTime 27 s ==========" indicates that there are 32 sockets in total, 22 sockets are not used, and it has been 27 seconds since the system starts.

