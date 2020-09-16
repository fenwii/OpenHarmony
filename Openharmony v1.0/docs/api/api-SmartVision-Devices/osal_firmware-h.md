# osal\_firmware.h<a name="ZH-CN_TOPIC_0000001054718101"></a>

## **Overview**<a name="section1859811124093526"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Declares firmware structures and interfaces. 

This file provides operations such as requesting and reading a firmware file, setting the offset for reading a firmware file, and releasing a firmware file. The firmware file can be read in split mode. The size of the firmware block to read each time is defined by the macro  **HDF\_FW\_BLOCK\_SIZE**. The firmware file is requested by calling  [OsalRequestFirmware](OSAL.md#ga428b9de7fb95a20ab9e25b47a7d4272c), the firmware block is read from the firmware file by calling  [OsalReadFirmware](OSAL.md#ga2b721d36c177786841cd05cecdb01034), and the firmware block can also be randomly read at a specified position by calling  [OsalSeekFirmware](OSAL.md#ga41ae4dade9246f3b30efd276cbd43474).

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1852145246093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1656155382093526"></a>
<table><thead align="left"><tr id="row212732704093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p148666347093526"><a name="p148666347093526"></a><a name="p148666347093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p719587701093526"><a name="p719587701093526"></a><a name="p719587701093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1652416593093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267739668093526"><a name="p1267739668093526"></a><a name="p1267739668093526"></a><a href="OsalFirmware.md">OsalFirmware</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064804283093526"><a name="p2064804283093526"></a><a name="p2064804283093526"></a>Defines the data structure for operating a firmware file. </p>
</td>
</tr>
<tr id="row1725386135093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132884992093526"><a name="p2132884992093526"></a><a name="p2132884992093526"></a><a href="OsalFwBlock.md">OsalFwBlock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370481522093526"><a name="p370481522093526"></a><a name="p370481522093526"></a>Defines the data structure for reading a firmware file. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1148441678093526"></a>
<table><thead align="left"><tr id="row137941390093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1029802265093526"><a name="p1029802265093526"></a><a name="p1029802265093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p113164390093526"><a name="p113164390093526"></a><a name="p113164390093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row694541348093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1540066994093526"><a name="p1540066994093526"></a><a name="p1540066994093526"></a><a href="OSAL.md#ga428b9de7fb95a20ab9e25b47a7d4272c">OsalRequestFirmware</a> (struct <a href="OsalFirmware.md">OsalFirmware</a> *fw, const char *fwName, void *device)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315965181093526"><a name="p315965181093526"></a><a name="p315965181093526"></a>int32_t&nbsp;</p>
<p id="p619781563093526"><a name="p619781563093526"></a><a name="p619781563093526"></a>Requests a firmware file based on its name and device information. </p>
</td>
</tr>
<tr id="row302551536093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p715465592093526"><a name="p715465592093526"></a><a name="p715465592093526"></a><a href="OSAL.md#ga41ae4dade9246f3b30efd276cbd43474">OsalSeekFirmware</a> (struct <a href="OsalFirmware.md">OsalFirmware</a> *fw, uint32_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206664929093526"><a name="p1206664929093526"></a><a name="p1206664929093526"></a>int32_t&nbsp;</p>
<p id="p260901368093526"><a name="p260901368093526"></a><a name="p260901368093526"></a>Reads a firmware file. </p>
</td>
</tr>
<tr id="row566556175093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1631701605093526"><a name="p1631701605093526"></a><a name="p1631701605093526"></a><a href="OSAL.md#ga2b721d36c177786841cd05cecdb01034">OsalReadFirmware</a> (struct <a href="OsalFirmware.md">OsalFirmware</a> *fw, struct <a href="OsalFwBlock.md">OsalFwBlock</a> *block)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p686828386093526"><a name="p686828386093526"></a><a name="p686828386093526"></a>int32_t&nbsp;</p>
<p id="p1010985164093526"><a name="p1010985164093526"></a><a name="p1010985164093526"></a>Releases a firmware file. </p>
</td>
</tr>
<tr id="row1670399765093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897350842093526"><a name="p1897350842093526"></a><a name="p1897350842093526"></a><a href="OSAL.md#gadfccddc78411a76ae8f4af4282da12f0">OsalReleaseFirmware</a> (struct <a href="OsalFirmware.md">OsalFirmware</a> *fw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p373991896093526"><a name="p373991896093526"></a><a name="p373991896093526"></a>int32_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

