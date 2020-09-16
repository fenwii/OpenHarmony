# hota\_updater.h<a name="ZH-CN_TOPIC_0000001054212845"></a>

## **Overview**<a name="section2143330661113025"></a>

**Related Modules:**

[OTA](OTA.md)

**Description:**

Defines the functions for system upgrades. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1292001675113025"></a>

## Functions<a name="func-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#gaad84182506ca52a6234f2dec6396103a">HotaSetPackageType</a> (unsigned int flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Sets the switch for using the default upgrade package format. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#ga0e8225985688805b8e729743d421b1a7">HotaGetUpdateIndex</a> (unsigned int *index)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Obtains the index of the A/B partition to be upgraded. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#ga0c102595fd53af136d5c53d42291ebf8">HotaInit</a> (ErrorCallBackFunc errorCallback, StatusCallBackFunc statusCallback)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Initializes the OTA module. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#ga3b2d7152e8898e5f1d95fcabaa181e40">HotaWrite</a> (unsigned char *buffer, unsigned int offset, unsigned int buffSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Writes specified data into flash memory. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#ga0972316900eaa074273a3c286c42d409">HotaRead</a> (unsigned int offset, unsigned int bufLen, unsigned char *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Reads the data that has been written into flash memory. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#ga12041eb3f4672051aaefa5eddaa863ff">HotaCancel</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Cancels an upgrade. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#ga017c1bd1166fd95dede1a28a87adb0fa">HotaSetBootSettings</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Sets the system state to be upgrading after data has been written into flash memory by <a href="OTA.md#ga3b2d7152e8898e5f1d95fcabaa181e40">HotaWrite</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="OTA.md#gad539df71d6fa124457e06badc0c05c46">HotaRestart</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Restarts the system after an upgrade. </p>
</td>
</tr>
</tbody>
</table>

