# rtc\_if.h<a name="ZH-CN_TOPIC_0000001054879510"></a>

## **Overview**<a name="section1105424938084832"></a>

**Related Modules:**

[RTC](RTC.md)

**Description:**

Declares the standard RTC APIs. 

**Since:**

1.0

## **Summary**<a name="section272281179084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1544710918084832"></a>
<table><thead align="left"><tr id="row1448615518084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1328362483084832"><a name="p1328362483084832"></a><a name="p1328362483084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1812726361084832"><a name="p1812726361084832"></a><a name="p1812726361084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1056135384084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952579935084832"><a name="p952579935084832"></a><a name="p952579935084832"></a><a href="RtcTime.md">RtcTime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27442609084832"><a name="p27442609084832"></a><a name="p27442609084832"></a>Defines the RTC information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1652545093084832"></a>
<table><thead align="left"><tr id="row1118501557084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2023925061084832"><a name="p2023925061084832"></a><a name="p2023925061084832"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1507219348084832"><a name="p1507219348084832"></a><a name="p1507219348084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1890588713084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904366389084832"><a name="p904366389084832"></a><a name="p904366389084832"></a><a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a>) (enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p953017801084832"><a name="p953017801084832"></a><a name="p953017801084832"></a>typedef int32_t(*&nbsp;</p>
<p id="p1114143924084832"><a name="p1114143924084832"></a><a name="p1114143924084832"></a>Defines a callback that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table689216364084832"></a>
<table><thead align="left"><tr id="row301356783084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1198479990084832"><a name="p1198479990084832"></a><a name="p1198479990084832"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1256953202084832"><a name="p1256953202084832"></a><a name="p1256953202084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1199250699084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1890793303084832"><a name="p1890793303084832"></a><a name="p1890793303084832"></a><a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> { <a href="RTC.md#ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b">RTC_ALARM_INDEX_A</a> = 0, <a href="RTC.md#ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352">RTC_ALARM_INDEX_B</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893383051084832"><a name="p893383051084832"></a><a name="p893383051084832"></a>Enumerates alarm indexes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1207751293084832"></a>
<table><thead align="left"><tr id="row1176332456084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p315582470084832"><a name="p315582470084832"></a><a name="p315582470084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p422332627084832"><a name="p422332627084832"></a><a name="p422332627084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1981232273084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p688747140084832"><a name="p688747140084832"></a><a name="p688747140084832"></a><a href="RTC.md#ga3fcf1d7f9bd17c501282a047923161fe">RtcOpen</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194571230084832"><a name="p194571230084832"></a><a name="p194571230084832"></a>struct <a href="DevHandle.md">DevHandle</a> *&nbsp;</p>
<p id="p1877815689084832"><a name="p1877815689084832"></a><a name="p1877815689084832"></a>Opens the RTC device to obtain its handle. </p>
</td>
</tr>
<tr id="row156431794084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1646225157084832"><a name="p1646225157084832"></a><a name="p1646225157084832"></a><a href="RTC.md#gabbf47f061b0f083066ec1da5bdbad9fe">RtcClose</a> (struct <a href="DevHandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1222968835084832"><a name="p1222968835084832"></a><a name="p1222968835084832"></a>void&nbsp;</p>
<p id="p723155687084832"><a name="p723155687084832"></a><a name="p723155687084832"></a>Releases a specified handle of the RTC device. </p>
</td>
</tr>
<tr id="row268630297084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255347555084832"><a name="p255347555084832"></a><a name="p255347555084832"></a><a href="RTC.md#gab3049a463cd2d18b098ae267ec4e9f48">RtcReadTime</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p836416048084832"><a name="p836416048084832"></a><a name="p836416048084832"></a>int32_t&nbsp;</p>
<p id="p1425025249084832"><a name="p1425025249084832"></a><a name="p1425025249084832"></a>Reads time from the RTC driver. </p>
</td>
</tr>
<tr id="row2004559093084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241732187084832"><a name="p241732187084832"></a><a name="p241732187084832"></a><a href="RTC.md#gaa1bfb39230ba3155d03702ad04af67b4">RtcWriteTime</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, const struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893278942084832"><a name="p893278942084832"></a><a name="p893278942084832"></a>int32_t&nbsp;</p>
<p id="p2020435184084832"><a name="p2020435184084832"></a><a name="p2020435184084832"></a>Writes format-compliant time to the RTC driver. </p>
</td>
</tr>
<tr id="row734806702084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476878587084832"><a name="p476878587084832"></a><a name="p476878587084832"></a><a href="RTC.md#ga3a82b2990f646c8bef671ba443691a8a">RtcReadAlarm</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202588262084832"><a name="p1202588262084832"></a><a name="p1202588262084832"></a>int32_t&nbsp;</p>
<p id="p2048018165084832"><a name="p2048018165084832"></a><a name="p2048018165084832"></a>Reads the RTC alarm time that was set last time. </p>
</td>
</tr>
<tr id="row1933764312084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220632658084832"><a name="p220632658084832"></a><a name="p220632658084832"></a><a href="RTC.md#gad63c5aafffb1f8bee44497f71de5de8f">RtcWriteAlarm</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, const struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p230258095084832"><a name="p230258095084832"></a><a name="p230258095084832"></a>int32_t&nbsp;</p>
<p id="p1169579715084832"><a name="p1169579715084832"></a><a name="p1169579715084832"></a>Writes the RTC alarm time based on the alarm index. </p>
</td>
</tr>
<tr id="row1863371656084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1216080396084832"><a name="p1216080396084832"></a><a name="p1216080396084832"></a><a href="RTC.md#gac40e57d996375e1762968b66dedb5914">RtcRegisterAlarmCallback</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, <a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a> cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350791579084832"><a name="p1350791579084832"></a><a name="p1350791579084832"></a>int32_t&nbsp;</p>
<p id="p546791658084832"><a name="p546791658084832"></a><a name="p546791658084832"></a>Registers <a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a> that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
<tr id="row153474676084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1512023601084832"><a name="p1512023601084832"></a><a name="p1512023601084832"></a><a href="RTC.md#ga9253cd3579500b86caccd67252291259">RtcAlarmInterruptEnable</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, uint8_t enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1252941869084832"><a name="p1252941869084832"></a><a name="p1252941869084832"></a>int32_t&nbsp;</p>
<p id="p1968121743084832"><a name="p1968121743084832"></a><a name="p1968121743084832"></a>Enables or disables alarm interrupts. </p>
</td>
</tr>
<tr id="row1098160625084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1908137309084832"><a name="p1908137309084832"></a><a name="p1908137309084832"></a><a href="RTC.md#gafde58faab893e2b4c4b2a836985463e7">RtcGetFreq</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint32_t *freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146498960084832"><a name="p1146498960084832"></a><a name="p1146498960084832"></a>int32_t&nbsp;</p>
<p id="p646338754084832"><a name="p646338754084832"></a><a name="p646338754084832"></a>Reads the RTC external frequency. </p>
</td>
</tr>
<tr id="row1873395779084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p958293597084832"><a name="p958293597084832"></a><a name="p958293597084832"></a><a href="RTC.md#ga740cb1ef1925f2c3bff31e4cfc83d745">RtcSetFreq</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint32_t freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155613957084832"><a name="p155613957084832"></a><a name="p155613957084832"></a>int32_t&nbsp;</p>
<p id="p363080458084832"><a name="p363080458084832"></a><a name="p363080458084832"></a>Sets the frequency of the external crystal oscillator connected to the RTC driver. </p>
</td>
</tr>
<tr id="row249573799084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1270169524084832"><a name="p1270169524084832"></a><a name="p1270169524084832"></a><a href="RTC.md#ga775682fde8d650c958e103832ff63dc9">RtcReset</a> (struct <a href="DevHandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p256830689084832"><a name="p256830689084832"></a><a name="p256830689084832"></a>int32_t&nbsp;</p>
<p id="p904649712084832"><a name="p904649712084832"></a><a name="p904649712084832"></a>Resets the RTC driver. </p>
</td>
</tr>
<tr id="row1244656611084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31266641084832"><a name="p31266641084832"></a><a name="p31266641084832"></a><a href="RTC.md#ga94acd2872dda4b0c487da7d106db3d60">RtcReadReg</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint8_t usrDefIndex, uint8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713400773084832"><a name="p1713400773084832"></a><a name="p1713400773084832"></a>int32_t&nbsp;</p>
<p id="p1425388575084832"><a name="p1425388575084832"></a><a name="p1425388575084832"></a>Reads the configuration of a custom RTC register based on the register index. </p>
</td>
</tr>
<tr id="row357085934084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1168710610084832"><a name="p1168710610084832"></a><a name="p1168710610084832"></a><a href="RTC.md#ga786f9e5a4c2731512c084b86f6f7a3a6">RtcWriteReg</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint8_t usrDefIndex, uint8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303651172084832"><a name="p303651172084832"></a><a name="p303651172084832"></a>int32_t&nbsp;</p>
<p id="p898936981084832"><a name="p898936981084832"></a><a name="p898936981084832"></a>Writes the configuration of a custom RTC register based on the register index. </p>
</td>
</tr>
</tbody>
</table>

