# OTA<a name="ZH-CN_TOPIC_0000001054652797"></a>

## **Overview**<a name="section792648629113022"></a>

Provides system upgrades. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1223608590113022"></a>

## Files<a name="files"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="hota_updater-h.md">hota_updater.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the functions for system upgrades. </p>
</td>
</tr>
</tbody>
</table>

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

## **Details**<a name="section1865529714113022"></a>

## **Function Documentation**<a name="section596164390113022"></a>

## HotaCancel\(\)<a name="ga12041eb3f4672051aaefa5eddaa863ff"></a>

```
int HotaCancel (void )
```

 **Description:**

Cancels an upgrade. 

If an upgrade fails or is interrupted, you can use this function to cancel it. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaGetUpdateIndex\(\)<a name="ga0e8225985688805b8e729743d421b1a7"></a>

```
int HotaGetUpdateIndex (unsigned int * index)
```

 **Description:**

Obtains the index of the A/B partition to be upgraded. 

In the A/B upgrade scenario, you can use this function to determine whether partition A or B will be upgraded. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of a partition. The value <strong>1</strong> means partition A, and <strong>2</strong> means partition B.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaInit\(\)<a name="ga0c102595fd53af136d5c53d42291ebf8"></a>

```
int HotaInit (ErrorCallBackFunc errorCallback, StatusCallBackFunc statusCallback )
```

 **Description:**

Initializes the OTA module. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">errorCallback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback invoked when an error occurs during the upgrade. This parameter can be null. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">statusCallback</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback invoked when the upgrade status changes. This parameter can be null.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaRead\(\)<a name="ga0972316900eaa074273a3c286c42d409"></a>

```
int HotaRead (unsigned int offset, unsigned int bufLen, unsigned char * buf )
```

 **Description:**

Reads the data that has been written into flash memory. 

This function is required for verifying data correctness when the default upgrade package format is not used. It is not required when the default upgrade package format is used. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">offset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the offset from where to start reading data. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bufLen</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to be read. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer to store the data that has been read.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaRestart\(\)<a name="gad539df71d6fa124457e06badc0c05c46"></a>

```
int HotaRestart (void )
```

 **Description:**

Restarts the system after an upgrade. 

You need to call this function after you have called the  [HotaSetBootSettings](OTA.md#ga017c1bd1166fd95dede1a28a87adb0fa)  function. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaSetBootSettings\(\)<a name="ga017c1bd1166fd95dede1a28a87adb0fa"></a>

```
int HotaSetBootSettings (void )
```

 **Description:**

Sets the system state to be upgrading after data has been written into flash memory by  [HotaWrite](OTA.md#ga3b2d7152e8898e5f1d95fcabaa181e40). 

After this operation is successful, you need to call the  [HotaRestart](OTA.md#gad539df71d6fa124457e06badc0c05c46)  function to complete the upgrade. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaSetPackageType\(\)<a name="gaad84182506ca52a6234f2dec6396103a"></a>

```
int HotaSetPackageType (unsigned int flag)
```

 **Description:**

Sets the switch for using the default upgrade package format. 

You can call this function to choose the default upgrade package format when developing the system upgrade capability. If the default upgrade package format is used, the system ensures the security and integrity of the upgrade package. If it is not used, you need to ensure the security and integrity of the upgrade package you have chosen. To be specific, you need to call the  [HotaRead](OTA.md#ga0972316900eaa074273a3c286c42d409)  function to read the data that has been written into flash memory, and then verify the data. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flag</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to use the default system upgrade package format. The value <strong>1</strong> (default value) means to use it, and <strong>0</strong> means not to use it.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HotaWrite\(\)<a name="ga3b2d7152e8898e5f1d95fcabaa181e40"></a>

```
int HotaWrite (unsigned char * buffer, unsigned int offset, unsigned int buffSize )
```

 **Description:**

Writes specified data into flash memory. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data to be written into flash memory. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">offset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the offset from where to start writing data. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffSize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the data to be written.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



