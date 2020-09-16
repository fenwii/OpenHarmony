# log<a name="EN-US_TOPIC_0000001052370295"></a>

## Command Function<a name="section128219131856"></a>

This command is used to modify and query log configurations.

## Syntax<a name="section3894181710519"></a>

log level \[_levelNum_\]

## Parameter Description<a name="section7693122310515"></a>

**Table  1**  Parameters

<a name="table237mcpsimp"></a>
<table><thead align="left"><tr id="row243mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p245mcpsimp"><a name="p245mcpsimp"></a><a name="p245mcpsimp"></a><strong id="b3369319192013"><a name="b3369319192013"></a><a name="b3369319192013"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p247mcpsimp"><a name="p247mcpsimp"></a><a name="p247mcpsimp"></a><strong id="b12646112413211"><a name="b12646112413211"></a><a name="b12646112413211"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p249mcpsimp"><a name="p249mcpsimp"></a><a name="p249mcpsimp"></a><strong id="b13881153318285"><a name="b13881153318285"></a><a name="b13881153318285"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row250mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p252mcpsimp"><a name="p252mcpsimp"></a><a name="p252mcpsimp"></a>levelNum</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p254mcpsimp"><a name="p254mcpsimp"></a><a name="p254mcpsimp"></a>Indicates the print level of configuration logs.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p256mcpsimp"><a name="p256mcpsimp"></a><a name="p256mcpsimp"></a>[0x0, 0x5]</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section1982111281512"></a>

-   This command depends on  **LOSCFG\_SHELL\_LK**. Before running this command, enable the  **Enable Shell lk**  configuration item using  **menuconfig**.

    Debug ---\> Enable a Debug Version ---\> Enable Shell ---\> Enable Shell lK

-   The  **log level**  command is used to configure log levels, which can be:

    TRACE\_EMG = 0,

    TRACE\_COMMON = 1,

    TRACE\_ERROR = 2,

    TRACE\_WARN = 3,

    TRACE\_INFO = 4,

    TRACE\_DEBUG = 5

    If the level is not within the valid range, a message is printed.

-   If the  **\[levelNum\]**  parameter is not specified, the current log level and its usage are printed by default.

## Example<a name="section176301333259"></a>

Enter  **log level 4**.

## Output<a name="section14354765415"></a>

![](figures/en-us_image_0000001052530298.png)

