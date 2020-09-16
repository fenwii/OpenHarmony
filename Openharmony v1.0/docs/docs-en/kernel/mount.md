# mount<a name="EN-US_TOPIC_0000001052530288"></a>

## Command Function<a name="section11631837182"></a>

This command is used to mount a device to a specified directory.

## Syntax<a name="section1697638111820"></a>

mount <_device_\> <_path_\> <_name_\> \[_uid gid_\]

## Parameter Description<a name="section1650151221819"></a>

**Table  1**  Parameters

<a name="table1338mcpsimp"></a>
<table><thead align="left"><tr id="row1344mcpsimp"><th class="cellrowborder" valign="top" width="21%" id="mcps1.2.4.1.1"><p id="p1346mcpsimp"><a name="p1346mcpsimp"></a><a name="p1346mcpsimp"></a><strong id="b84913249612"><a name="b84913249612"></a><a name="b84913249612"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="52%" id="mcps1.2.4.1.2"><p id="p1348mcpsimp"><a name="p1348mcpsimp"></a><a name="p1348mcpsimp"></a><strong id="b1136292612616"><a name="b1136292612616"></a><a name="b1136292612616"></a>Description</strong></p>
</th>
<th class="cellrowborder" valign="top" width="27%" id="mcps1.2.4.1.3"><p id="p1350mcpsimp"><a name="p1350mcpsimp"></a><a name="p1350mcpsimp"></a><strong id="b4385271067"><a name="b4385271067"></a><a name="b4385271067"></a>Value Range</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1351mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1353mcpsimp"><a name="p1353mcpsimp"></a><a name="p1353mcpsimp"></a>device</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1355mcpsimp"><a name="p1355mcpsimp"></a><a name="p1355mcpsimp"></a>Indicates the path of the device to be mounted. The format is the path of the device.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1357mcpsimp"><a name="p1357mcpsimp"></a><a name="p1357mcpsimp"></a>A device in the system</p>
</td>
</tr>
<tr id="row1358mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1360mcpsimp"><a name="p1360mcpsimp"></a><a name="p1360mcpsimp"></a>path</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1362mcpsimp"><a name="p1362mcpsimp"></a><a name="p1362mcpsimp"></a>Indicates the directory of the device.</p>
<p id="p1363mcpsimp"><a name="p1363mcpsimp"></a><a name="p1363mcpsimp"></a>The user must have the execution (search) permission for the specified directory.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1365mcpsimp"><a name="p1365mcpsimp"></a><a name="p1365mcpsimp"></a>N/A</p>
</td>
</tr>
<tr id="row1366mcpsimp"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p1368mcpsimp"><a name="p1368mcpsimp"></a><a name="p1368mcpsimp"></a>name</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p1370mcpsimp"><a name="p1370mcpsimp"></a><a name="p1370mcpsimp"></a>Indicates the file system type.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p1372mcpsimp"><a name="p1372mcpsimp"></a><a name="p1372mcpsimp"></a>vfat, yaffs, jffs, ramfs, nfs, procfs, romfs</p>
</td>
</tr>
<tr id="row138821392219"><td class="cellrowborder" valign="top" width="21%" headers="mcps1.2.4.1.1 "><p id="p15883891213"><a name="p15883891213"></a><a name="p15883891213"></a>uid gid</p>
</td>
<td class="cellrowborder" valign="top" width="52%" headers="mcps1.2.4.1.2 "><p id="p158834917217"><a name="p158834917217"></a><a name="p158834917217"></a><strong id="b1647703019395"><a name="b1647703019395"></a><a name="b1647703019395"></a>uid</strong> indicates the user ID.</p>
<p id="p18500185615215"><a name="p18500185615215"></a><a name="p18500185615215"></a><strong id="b13341343114017"><a name="b13341343114017"></a><a name="b13341343114017"></a>gid</strong> indicates the group ID.</p>
<p id="p519052614387"><a name="p519052614387"></a><a name="p519052614387"></a>This parameter is optional. The default values are <strong id="b586915244111"><a name="b586915244111"></a><a name="b586915244111"></a>uid:0</strong> and <strong id="b1471656417"><a name="b1471656417"></a><a name="b1471656417"></a>gid:0</strong>.</p>
</td>
<td class="cellrowborder" valign="top" width="27%" headers="mcps1.2.4.1.3 "><p id="p178835919211"><a name="p178835919211"></a><a name="p178835919211"></a>N/A</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section124541520171912"></a>

By specifying the device to be mounted, directory, and file system format in the  **mount**  command, you can successfully mount the file system to the specified directory.

## Example<a name="section7424625171917"></a>

Enter  **mount /dev/mmcblk0p0 /bin1/vs/sd vfat**.

## Output<a name="section14757018116"></a>

Mounting  **/dev/mmcblk0p0**  to the  **/bin1/vs/sd**  directory

![](figures/en-us_image_0000001051690323.png)

