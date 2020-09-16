# kill<a name="EN-US_TOPIC_0000001053719629"></a>

## Command Function<a name="section366714216619"></a>

This command is used to send a specific signal to a specified process.

## Syntax<a name="section8833164614615"></a>

kill \[_signo_  |  _-signo_\] \[_pid_\]

## Parameter Description<a name="section12809111019453"></a>

**Table  1**  Parameters

<a name="table438mcpsimp"></a>
<table><thead align="left"><tr id="row444mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p446mcpsimp"><a name="p446mcpsimp"></a><a name="p446mcpsimp"></a><strong id="b105624422368"><a name="b105624422368"></a><a name="b105624422368"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="51.92%" id="mcps1.2.4.1.2"><p id="p448mcpsimp"><a name="p448mcpsimp"></a><a name="p448mcpsimp"></a><strong id="b109117451362"><a name="b109117451362"></a><a name="b109117451362"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27.08%" id="mcps1.2.4.1.3"><p id="p450mcpsimp"><a name="p450mcpsimp"></a><a name="p450mcpsimp"></a><strong id="b1410453910286"><a name="b1410453910286"></a><a name="b1410453910286"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row451mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2500105121818"><a name="p2500105121818"></a><a name="p2500105121818"></a>signo</p>
</td>
<td class="cellrowborder" valign="top" width="51.92%" headers="mcps1.2.4.1.2 "><p id="p1149945111817"><a name="p1149945111817"></a><a name="p1149945111817"></a>Indicates the signal ID.</p>
</td>
<td class="cellrowborder" valign="top" width="27.08%" headers="mcps1.2.4.1.3 "><p id="p749810571812"><a name="p749810571812"></a><a name="p749810571812"></a>[1, 30]</p>
</td>
</tr>
<tr id="row113001232165611"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p18301173213562"><a name="p18301173213562"></a><a name="p18301173213562"></a>pid</p>
</td>
<td class="cellrowborder" valign="top" width="51.92%" headers="mcps1.2.4.1.2 "><p id="p1730143212569"><a name="p1730143212569"></a><a name="p1730143212569"></a>Indicates the process ID.</p>
</td>
<td class="cellrowborder" valign="top" width="27.08%" headers="mcps1.2.4.1.3 "><p id="p1301193275618"><a name="p1301193275618"></a><a name="p1301193275618"></a>[1, MAX_INT]</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-notice.gif) **NOTICE:** 
>The valid range of the  **signo**  value is \[0, 64\], and the recommended value range is \[1, 30\]. Other values in the valid range are reserved.

## Usage<a name="section15935131220717"></a>

The  **signo**  and  **pid**  parameters are mandatory.

The  **pid**  value range varies depending on the system configuration. For example, if the maximum  **pid**  value supported by the system is  **256**, this value range is \[1-256\].

## Example<a name="section79281818476"></a>

1.  Query the current process list and determine the PID \(7\) of the process to be killed.

**Figure  1**  Querying PIDs<a name="fig6133125414256"></a>  
![](figures/querying-pids.png "querying-pids")

2. Run  **kill 14 7**  to send signal 14 \(the default behavior of  **SIGALRM**  is to terminate the process\) to process 7  **helloworld\_d**  \(user-space\). Then query the current process list. Process 7 has been terminated. The result of the  **kill 14 7**  command is the same as that of the  **kill -14 7**  command.

**Figure  2**  Command output<a name="fig2281711563"></a>  
![](figures/command-output.png "command-output")

## Output<a name="section12742311179"></a>

The command output is as follows:

**Figure  3**  Sending a signal to a specified process<a name="fig11800272147"></a>  
![](figures/sending-a-signal-to-a-specified-process.png "sending-a-signal-to-a-specified-process")

The signal is successfully sent if no error is reported.

**Figure  4**  Signal sending failure<a name="fig24081235151813"></a>  
![](figures/signal-sending-failure.png "signal-sending-failure")

The preceding figure shows a signal sending failure caused by invalid parameters. In this case, check that the signal ID and PID are valid.

