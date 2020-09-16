# telnet<a name="EN-US_TOPIC_0000001051611544"></a>

## Command Function<a name="section3551830123913"></a>

This command is used to enable or disable the Telnet server service.

## Syntax<a name="section14897133233918"></a>

telnet \[_on | off_\]

## Parameter Description<a name="section977718353392"></a>

**Table  1**  Parameters

<a name="table2844mcpsimp"></a>
<table><thead align="left"><tr id="row2850mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p2852mcpsimp"><a name="p2852mcpsimp"></a><a name="p2852mcpsimp"></a><strong id="b980352831178"><a name="b980352831178"></a><a name="b980352831178"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p2854mcpsimp"><a name="p2854mcpsimp"></a><a name="p2854mcpsimp"></a><strong id="b385431525416"><a name="b385431525416"></a><a name="b385431525416"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p2856mcpsimp"><a name="p2856mcpsimp"></a><a name="p2856mcpsimp"></a><strong id="b19001516841178"><a name="b19001516841178"></a><a name="b19001516841178"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row2857mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2859mcpsimp"><a name="p2859mcpsimp"></a><a name="p2859mcpsimp"></a>on</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2861mcpsimp"><a name="p2861mcpsimp"></a><a name="p2861mcpsimp"></a>Enables the Telnet server service.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2863mcpsimp"><a name="p2863mcpsimp"></a><a name="p2863mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row2864mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p2866mcpsimp"><a name="p2866mcpsimp"></a><a name="p2866mcpsimp"></a>off</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p2868mcpsimp"><a name="p2868mcpsimp"></a><a name="p2868mcpsimp"></a>Disables the Telnet server service.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p2870mcpsimp"><a name="p2870mcpsimp"></a><a name="p2870mcpsimp"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section134991538183916"></a>

-   Before enabling Telnet, ensure that the network driver and network protocol stack have been initialized and the NIC of the board is in the  **link up**  state.
-   Currently, multiple clients \(Telnet + IP\) cannot connect to the development board at the same time.

    >![](public_sys-resources/icon-notice.gif) **NOTICE:** 
    >Telnet is under debugging and disabled by default. Do not use it in formal products.


## Example<a name="section1097414426398"></a>

Enter  **telnet on**.

## Output<a name="section11846624191310"></a>

**Figure  1**  Output of  **telnet on**<a name="fig127221042155418"></a>  
![](figures/output-of-telnet-on.png "output-of-telnet-on")

