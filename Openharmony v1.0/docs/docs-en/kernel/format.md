# format<a name="EN-US_TOPIC_0000001051611540"></a>

## Command Function<a name="section1922331919169"></a>

This command is used to format a disk.

## Syntax<a name="section249226169"></a>

format <_dev\_inodename_\> <_sectors_\> <_option_\> \[_label_\]

## Parameter Description<a name="section985173416177"></a>

**Table  1**  Parameters

<a name="table1183mcpsimp"></a>
<table><thead align="left"><tr id="row1188mcpsimp"><th class="cellrowborder" valign="top" width="34%" id="mcps1.2.3.1.1"><p id="p1190mcpsimp"><a name="p1190mcpsimp"></a><a name="p1190mcpsimp"></a><strong id="b101095916104"><a name="b101095916104"></a><a name="b101095916104"></a>Parameter</strong></p>
</th>
<th class="cellrowborder" valign="top" width="66%" id="mcps1.2.3.1.2"><p id="p1192mcpsimp"><a name="p1192mcpsimp"></a><a name="p1192mcpsimp"></a><strong id="b14213111171020"><a name="b14213111171020"></a><a name="b14213111171020"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row1193mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1195mcpsimp"><a name="p1195mcpsimp"></a><a name="p1195mcpsimp"></a>dev_inodename</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><p id="p1197mcpsimp"><a name="p1197mcpsimp"></a><a name="p1197mcpsimp"></a>Indicates the device name.</p>
</td>
</tr>
<tr id="row1203mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1205mcpsimp"><a name="p1205mcpsimp"></a><a name="p1205mcpsimp"></a>sectors</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><p id="p1207mcpsimp"><a name="p1207mcpsimp"></a><a name="p1207mcpsimp"></a>Indicates the size of the allocated memory unit or sector. The value <strong id="b1574273871018"><a name="b1574273871018"></a><a name="b1574273871018"></a>0</strong> indicates that the parameter is null. (The value must be <strong id="b16428721113"><a name="b16428721113"></a><a name="b16428721113"></a>0</strong> or a power of <strong id="b1053419931111"><a name="b1053419931111"></a><a name="b1053419931111"></a>2</strong>. For FAT32, the maximum value is <strong id="b51473841110"><a name="b51473841110"></a><a name="b51473841110"></a>128</strong>. If the parameter is set to <strong id="b99547931214"><a name="b99547931214"></a><a name="b99547931214"></a>0</strong>, a proper cluster size is automatically selected. The available cluster size range varies depending on the partition size. If the cluster size is incorrectly specified, the formatting may fail.)</p>
</td>
</tr>
<tr id="row1208mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1210mcpsimp"><a name="p1210mcpsimp"></a><a name="p1210mcpsimp"></a>option</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><div class="p" id="p1212mcpsimp"><a name="p1212mcpsimp"></a><a name="p1212mcpsimp"></a>Indicates the formatting option for selecting the file system type. The options are as follows:<a name="ul10971366369"></a><a name="ul10971366369"></a><ul id="ul10971366369"><li><strong id="b169384514517"><a name="b169384514517"></a><a name="b169384514517"></a>0x01</strong>: FMT_FAT</li><li><strong id="b143061510125114"><a name="b143061510125114"></a><a name="b143061510125114"></a>0x02</strong>: FMT_FAT32</li><li><strong id="b3245614165116"><a name="b3245614165116"></a><a name="b3245614165116"></a>0x07</strong>: FMT_ANY</li><li><strong id="b018121813512"><a name="b018121813512"></a><a name="b018121813512"></a>0x08</strong>: FMT_ERASE (not supported by the USB flash drive)</li></ul>
</div>
<p id="p28366459374"><a name="p28366459374"></a><a name="p28366459374"></a>Other values are invalid. The system will automatically select the formatting mode. If the low-level formatting bit is 1 during the formatting of a USB flash drive, an error message is printed.</p>
</td>
</tr>
<tr id="row1213mcpsimp"><td class="cellrowborder" valign="top" width="34%" headers="mcps1.2.3.1.1 "><p id="p1215mcpsimp"><a name="p1215mcpsimp"></a><a name="p1215mcpsimp"></a>label</p>
</td>
<td class="cellrowborder" valign="top" width="66%" headers="mcps1.2.3.1.2 "><p id="p1217mcpsimp"><a name="p1217mcpsimp"></a><a name="p1217mcpsimp"></a>Indicates the volume label name. This parameter is optional, and the value is a string. If <strong id="b16648426102713"><a name="b16648426102713"></a><a name="b16648426102713"></a>null</strong> is specified for this parameter, the previously set volume label name is cleared.</p>
</td>
</tr>
</tbody>
</table>

## Usage<a name="section1510162714162"></a>

-   The  **format**  command is used to format a disk. You can find the device name in the  **dev**  directory. A storage card must be installed before the formatting.
-   This command can be used to format only the USB flash drive, SD card, and MMC, but not the NAND flash and NOR flash.
-   The  **sectors**  parameter must be set to a valid value. An invalid value may cause exceptions.

## Example<a name="section25691431161611"></a>

Enter  **format /dev/mmcblk0 128 2**.

## Output<a name="section17368112365920"></a>

Formatting result

![](figures/en-us_image_0000001052370307.png)

