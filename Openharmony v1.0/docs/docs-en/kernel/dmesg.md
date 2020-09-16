# dmesg<a name="EN-US_TOPIC_0000001052530284"></a>

## Command Function<a name="section4643204919313"></a>

This command is used to control the dmesg buffer of the kernel.

## Syntax<a name="section6553153635"></a>

dmesg

dmesg \[_-c/-C/-D/-E/-L/-U_\]

dmesg -s \[_size_\]

dmesg -l \[_level_\]

dmesg \> \[_fileA_\]

## Parameter Description<a name="section208971157532"></a>

**Table  1**  Parameters

<a name="table3900mcpsimp"></a>
<table><thead align="left"><tr id="row3906mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p3908mcpsimp"><a name="p3908mcpsimp"></a><a name="p3908mcpsimp"></a><strong id="b1396020482284"><a name="b1396020482284"></a><a name="b1396020482284"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p3910mcpsimp"><a name="p3910mcpsimp"></a><a name="p3910mcpsimp"></a><strong id="b5731534293"><a name="b5731534293"></a><a name="b5731534293"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p3912mcpsimp"><a name="p3912mcpsimp"></a><a name="p3912mcpsimp"></a><strong id="b46901499297"><a name="b46901499297"></a><a name="b46901499297"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row3913mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3915mcpsimp"><a name="p3915mcpsimp"></a><a name="p3915mcpsimp"></a>-c</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3917mcpsimp"><a name="p3917mcpsimp"></a><a name="p3917mcpsimp"></a>Prints content in the buffer and clears the buffer.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3919mcpsimp"><a name="p3919mcpsimp"></a><a name="p3919mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3920mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3922mcpsimp"><a name="p3922mcpsimp"></a><a name="p3922mcpsimp"></a>-C</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3924mcpsimp"><a name="p3924mcpsimp"></a><a name="p3924mcpsimp"></a>Clears the buffer.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3926mcpsimp"><a name="p3926mcpsimp"></a><a name="p3926mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3927mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3929mcpsimp"><a name="p3929mcpsimp"></a><a name="p3929mcpsimp"></a>-D/-E</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3931mcpsimp"><a name="p3931mcpsimp"></a><a name="p3931mcpsimp"></a>Enables or disables printing to the console.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3933mcpsimp"><a name="p3933mcpsimp"></a><a name="p3933mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3934mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3936mcpsimp"><a name="p3936mcpsimp"></a><a name="p3936mcpsimp"></a>-L/-U</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3938mcpsimp"><a name="p3938mcpsimp"></a><a name="p3938mcpsimp"></a>Enables or disables printing via the serial port.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3940mcpsimp"><a name="p3940mcpsimp"></a><a name="p3940mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3941mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3943mcpsimp"><a name="p3943mcpsimp"></a><a name="p3943mcpsimp"></a>-s size</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3945mcpsimp"><a name="p3945mcpsimp"></a><a name="p3945mcpsimp"></a>Sets the size of the buffer.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3947mcpsimp"><a name="p3947mcpsimp"></a><a name="p3947mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row3948mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3950mcpsimp"><a name="p3950mcpsimp"></a><a name="p3950mcpsimp"></a>-l level</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3952mcpsimp"><a name="p3952mcpsimp"></a><a name="p3952mcpsimp"></a>Sets the buffering level.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3954mcpsimp"><a name="p3954mcpsimp"></a><a name="p3954mcpsimp"></a>0 - 5</p>
</td>
</tr>
<tr id="row3955mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p3957mcpsimp"><a name="p3957mcpsimp"></a><a name="p3957mcpsimp"></a>&gt; fileA</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p3959mcpsimp"><a name="p3959mcpsimp"></a><a name="p3959mcpsimp"></a>Writes the content in the buffer to a file.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p3961mcpsimp"><a name="p3961mcpsimp"></a><a name="p3961mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section213115219413"></a>

-   This command depends on  **LOSCFG\_SHELL\_DMESG**. Before running this command, enable the  **Enable Shell dmesg**  configuration item using  **menuconfig**.

    Debug  ---\> Enable a Debug Version ---\> Enable Shell ---\> Enable Shell dmesg

-   If the parameters are not specified, all content in the buffer is printed.
-   The parameters followed by hyphens \(-\) are mutually exclusive.
    1.  Before writing content to a file, ensure that the file system has been mounted.
    2.  Disabling the serial port printing will adversely affect the shell. You are advised to set up a connection using Telnet before disabling the serial port.


## Example<a name="section13736564418"></a>

Enter  **dmesg \> /usr/dmesg.log**.

## Output<a name="section194005101413"></a>

**Figure  1**  Writing dmesg content to a file<a name="fig11150135113566"></a>  
![](figures/writing-dmesg-content-to-a-file.png "writing-dmesg-content-to-a-file")

