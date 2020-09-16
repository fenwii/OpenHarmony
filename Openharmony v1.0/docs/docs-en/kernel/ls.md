# ls<a name="EN-US_TOPIC_0000001051451593"></a>

## Command Function<a name="section6538163771614"></a>

This command is used to display the content of a specified directory.

## Syntax<a name="section45881743111616"></a>

ls \[_path_\]

## Parameter Description<a name="section17528148171617"></a>

**Table  1**  Parameters

<a name="table1244mcpsimp"></a>
<table><thead align="left"><tr id="row1250mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1252mcpsimp"><a name="p1252mcpsimp"></a><a name="p1252mcpsimp"></a><strong id="b85851402216"><a name="b85851402216"></a><a name="b85851402216"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1254mcpsimp"><a name="p1254mcpsimp"></a><a name="p1254mcpsimp"></a><strong id="b128175424215"><a name="b128175424215"></a><a name="b128175424215"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1256mcpsimp"><a name="p1256mcpsimp"></a><a name="p1256mcpsimp"></a><strong id="b184580431629"><a name="b184580431629"></a><a name="b184580431629"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1257mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1259mcpsimp"><a name="p1259mcpsimp"></a><a name="p1259mcpsimp"></a>path</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1261mcpsimp"><a name="p1261mcpsimp"></a><a name="p1261mcpsimp"></a>If <strong id="b115515262034"><a name="b115515262034"></a><a name="b115515262034"></a>path</strong> is left blank, the content of the current directory is displayed.</p>
<p id="p1262mcpsimp"><a name="p1262mcpsimp"></a><a name="p1262mcpsimp"></a>If the <strong id="b9593204114312"><a name="b9593204114312"></a><a name="b9593204114312"></a>path</strong> value is an invalid file name, the following failure message is displayed:</p>
<p id="p1263mcpsimp"><a name="p1263mcpsimp"></a><a name="p1263mcpsimp"></a><strong id="b19604131716416"><a name="b19604131716416"></a><a name="b19604131716416"></a>ls error: No such directory</strong></p>
<p id="p1264mcpsimp"><a name="p1264mcpsimp"></a><a name="p1264mcpsimp"></a>If the <strong id="b615314272412"><a name="b615314272412"></a><a name="b615314272412"></a>path</strong> value is a valid directory, the content of this directory is displayed.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><a name="ul103920301451"></a><a name="ul103920301451"></a><ul id="ul103920301451"><li>Left blank</li><li>A valid directory</li></ul>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section041212533166"></a>

-   This command can be used to display the content of the current directory.
-   This command can also display the size of a file.
-   The  **ls**  command with the  **proc**  directory passed cannot calculate the file size and  **0**  is displayed in the command output.

## Example<a name="section986105716167"></a>

Enter  **ls**.

## Output<a name="section2036124918592"></a>

**Figure  1**  Viewing content of the current directory<a name="fig17933775508"></a>  
![](figures/viewing-content-of-the-current-directory.png "viewing-content-of-the-current-directory")

