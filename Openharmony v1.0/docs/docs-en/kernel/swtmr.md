# swtmr<a name="EN-US_TOPIC_0000001051611538"></a>

## Command Function<a name="section166171064814"></a>

This command is used to query information about system software timers.

## Syntax<a name="section424011111682"></a>

swtmr \[_ID_\]

## Parameter Description<a name="section1268410459465"></a>

**Table  1**  Parameters

<a name="table517mcpsimp"></a>
<table><thead align="left"><tr id="row523mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p525mcpsimp"><a name="p525mcpsimp"></a><a name="p525mcpsimp"></a><strong id="b28751015911"><a name="b28751015911"></a><a name="b28751015911"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p527mcpsimp"><a name="p527mcpsimp"></a><a name="p527mcpsimp"></a><strong id="b16241861799"><a name="b16241861799"></a><a name="b16241861799"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p529mcpsimp"><a name="p529mcpsimp"></a><a name="p529mcpsimp"></a><strong id="b2712206132817"><a name="b2712206132817"></a><a name="b2712206132817"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row530mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p532mcpsimp"><a name="p532mcpsimp"></a><a name="p532mcpsimp"></a>ID</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p534mcpsimp"><a name="p534mcpsimp"></a><a name="p534mcpsimp"></a>Indicates the ID of a software timer.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p536mcpsimp"><a name="p536mcpsimp"></a><a name="p536mcpsimp"></a>[0, 0xFFFFFFFF]</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section169806213815"></a>

-   If the parameter is not specified, information about all software timers is displayed.
-   If the  **ID**  parameter is specified, information about the specified software timer is displayed.

## Example<a name="section16676026389"></a>

Enter  **swtmr**  and  **swtmr 1**.

## Output<a name="section1541991614710"></a>

**Figure  1**  Querying information about all software timers<a name="fig9860611451"></a>  
![](figures/querying-information-about-all-software-timers.png "querying-information-about-all-software-timers")

**Figure  2**  Querying information about a specified software timer<a name="fig22051415124512"></a>  
![](figures/querying-information-about-a-specified-software-timer.png "querying-information-about-a-specified-software-timer")

**Table  2**  Output description

<a name="table551mcpsimp"></a>
<table><thead align="left"><tr id="row556mcpsimp"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p558mcpsimp"><a name="p558mcpsimp"></a><a name="p558mcpsimp"></a>Parameter</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p560mcpsimp"><a name="p560mcpsimp"></a><a name="p560mcpsimp"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row561mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p563mcpsimp"><a name="p563mcpsimp"></a><a name="p563mcpsimp"></a>SwTmrID</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p565mcpsimp"><a name="p565mcpsimp"></a><a name="p565mcpsimp"></a>Indicates the ID of the software timer.</p>
</td>
</tr>
<tr id="row566mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p568mcpsimp"><a name="p568mcpsimp"></a><a name="p568mcpsimp"></a>State</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p570mcpsimp"><a name="p570mcpsimp"></a><a name="p570mcpsimp"></a>Indicates the status of the software timer.</p>
<p id="p88402543474"><a name="p88402543474"></a><a name="p88402543474"></a>The value can be <strong id="b10351548112016"><a name="b10351548112016"></a><a name="b10351548112016"></a>UnUsed</strong>, <strong id="b1714715501204"><a name="b1714715501204"></a><a name="b1714715501204"></a>Created</strong>, or <strong id="b36981653142018"><a name="b36981653142018"></a><a name="b36981653142018"></a>Ticking</strong>.</p>
</td>
</tr>
<tr id="row571mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p573mcpsimp"><a name="p573mcpsimp"></a><a name="p573mcpsimp"></a>Mode</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p575mcpsimp"><a name="p575mcpsimp"></a><a name="p575mcpsimp"></a>Indicates the mode of the software timer.</p>
<p id="p657320204499"><a name="p657320204499"></a><a name="p657320204499"></a>The value can be <strong id="b1291181502310"><a name="b1291181502310"></a><a name="b1291181502310"></a>Once</strong>, <strong id="b12266317112316"><a name="b12266317112316"></a><a name="b12266317112316"></a>Period</strong>, or <strong id="b1736331919234"><a name="b1736331919234"></a><a name="b1736331919234"></a>NSD</strong> (one-time timer that will not be automatically deleted after the timer expires).</p>
</td>
</tr>
<tr id="row576mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p578mcpsimp"><a name="p578mcpsimp"></a><a name="p578mcpsimp"></a>Interval</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p580mcpsimp"><a name="p580mcpsimp"></a><a name="p580mcpsimp"></a>Indicates the number of ticks used by the software timer.</p>
</td>
</tr>
<tr id="row581mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p583mcpsimp"><a name="p583mcpsimp"></a><a name="p583mcpsimp"></a>Count</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p585mcpsimp"><a name="p585mcpsimp"></a><a name="p585mcpsimp"></a>Indicates the number of times that the software timer has been working.</p>
</td>
</tr>
<tr id="row586mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p588mcpsimp"><a name="p588mcpsimp"></a><a name="p588mcpsimp"></a>Arg</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p590mcpsimp"><a name="p590mcpsimp"></a><a name="p590mcpsimp"></a>Indicates the input parameter.</p>
</td>
</tr>
<tr id="row591mcpsimp"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p593mcpsimp"><a name="p593mcpsimp"></a><a name="p593mcpsimp"></a>handlerAddr</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p595mcpsimp"><a name="p595mcpsimp"></a><a name="p595mcpsimp"></a>Indicates the callback address.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>-   The  **ID**  value can be in decimal or hexadecimal format.
>-   If the  **ID**  value is within the range of \[0,  _Number of current software timers - 1_\], the status of the specified software timer is returned. For other values, an error message is displayed.

