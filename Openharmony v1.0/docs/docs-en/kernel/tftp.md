# tftp<a name="EN-US_TOPIC_0000001051451597"></a>

## Command Function<a name="section15142134573911"></a>

Trivial File Transfer Protocol \(TFTP\) is a protocol in the TCP/IP protocol suite for transferring files between clients and servers. TFTP provides simple and low-overhead file transfer services. The port number is 69.

The  **tftp**  command is used to download files from the TFTP server.

## Syntax<a name="section20958174917394"></a>

tftp  _<-g/-p\>_ _-l_ _\[FullPathLocalFile\] -r \[RemoteFile\] \[Host\]_

## Parameter Description<a name="section576613532395"></a>

**Table  1**  Parameters

<a name="table2894mcpsimp"></a>
<table><thead align="left"><tr id="row2900mcpsimp"><th class="cellrowborder" valign="top" width="20.79%" id="mcps1.2.4.1.1"><p id="p2902mcpsimp"><a name="p2902mcpsimp"></a><a name="p2902mcpsimp"></a><strong id="b116998706011737"><a name="b116998706011737"></a><a name="b116998706011737"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52.480000000000004%" id="mcps1.2.4.1.2"><p id="p2904mcpsimp"><a name="p2904mcpsimp"></a><a name="p2904mcpsimp"></a><strong id="b13511135745719"><a name="b13511135745719"></a><a name="b13511135745719"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="26.729999999999997%" id="mcps1.2.4.1.3"><p id="p2906mcpsimp"><a name="p2906mcpsimp"></a><a name="p2906mcpsimp"></a><strong id="b174218805911737"><a name="b174218805911737"></a><a name="b174218805911737"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row2907mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2909mcpsimp"><a name="p2909mcpsimp"></a><a name="p2909mcpsimp"></a>-g/-p</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2911mcpsimp"><a name="p2911mcpsimp"></a><a name="p2911mcpsimp"></a>Indicates the file transfer direction.</p>
<a name="ul73571240131312"></a><a name="ul73571240131312"></a><ul id="ul73571240131312"><li><strong id="b0778214125818"><a name="b0778214125818"></a><a name="b0778214125818"></a>-g</strong>: downloads files from the TFTP server.</li><li><strong id="b7168132555814"><a name="b7168132555814"></a><a name="b7168132555814"></a>-p</strong>: uploads files to the TFTP server.</li></ul>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="p14399194271310"><a name="p14399194271310"></a><a name="p14399194271310"></a>N/A</p>
</td>
</tr>
<tr id="row2921mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2923mcpsimp"><a name="p2923mcpsimp"></a><a name="p2923mcpsimp"></a>-l FullPathLocalFile</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2925mcpsimp"><a name="p2925mcpsimp"></a><a name="p2925mcpsimp"></a>Indicates the complete path of a local file.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2926mcpsimpp0"><a name="entry2926mcpsimpp0"></a><a name="entry2926mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row2927mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2929mcpsimp"><a name="p2929mcpsimp"></a><a name="p2929mcpsimp"></a>-r RemoteFile</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2931mcpsimp"><a name="p2931mcpsimp"></a><a name="p2931mcpsimp"></a>Indicates the file name on the server.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2932mcpsimpp0"><a name="entry2932mcpsimpp0"></a><a name="entry2932mcpsimpp0"></a>N/A</p>
</td>
</tr>
<tr id="row2933mcpsimp"><td class="cellrowborder" valign="top" width="20.79%" headers="mcps1.2.4.1.1 "><p id="p2935mcpsimp"><a name="p2935mcpsimp"></a><a name="p2935mcpsimp"></a>Host</p>
</td>
<td class="cellrowborder" valign="top" width="52.480000000000004%" headers="mcps1.2.4.1.2 "><p id="p2937mcpsimp"><a name="p2937mcpsimp"></a><a name="p2937mcpsimp"></a>Indicates the server IP address.</p>
</td>
<td class="cellrowborder" valign="top" width="26.729999999999997%" headers="mcps1.2.4.1.3 "><p id="entry2938mcpsimpp0"><a name="entry2938mcpsimpp0"></a><a name="entry2938mcpsimpp0"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section149795134408"></a>

1.  Deploy a TFTP server on the server and configure the TFTP server correctly.
2.  Use the  **tftp**  command to upload and download files on the OpenHarmony board.
3.  The size of the file to be transferred cannot exceed 32 MB.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >TFTP is under debugging and disabled by default. Do not use it in formal products.


## Example<a name="section148921918114015"></a>

Download the  **out**  file from the server.

## Output<a name="section7872155631313"></a>

```
OHOS # tftp -g -l /nfs/out -r out 192.168.1.2
TFTP transfer finish
```

After the  **tftp**  command is executed,  **TFTP transfer finish**  is displayed if the file transfer is complete. If the file transfer fails, other information is displayed to help locate the fault.

