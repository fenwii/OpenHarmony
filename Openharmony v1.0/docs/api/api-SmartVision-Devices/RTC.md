# RTC<a name="ZH-CN_TOPIC_0000001055039466"></a>

## **Overview**<a name="section1745924797084825"></a>

Provides standard real-time clock \(RTC\) APIs. 

These APIs allow you to perform operations such as reading or writing system time, reading or writing alarm time, setting alarm interrupts, registering alarm callbacks, setting the external frequency, resetting the RTC driver, and customizing RTC configurations. The RTC driver provides precise real time for the operating system \(OS\). If the OS is powered off, the RTC driver continues to keep track of the system time using an external battery.

**Since:**

1.0

## **Summary**<a name="section59599383084825"></a>

## Files<a name="files"></a>

<a name="table437804007084825"></a>
<table><thead align="left"><tr id="row1946864335084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1377138913084825"><a name="p1377138913084825"></a><a name="p1377138913084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1587075123084825"><a name="p1587075123084825"></a><a name="p1587075123084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1922928510084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1448658077084825"><a name="p1448658077084825"></a><a name="p1448658077084825"></a><a href="rtc_if-h.md">rtc_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p460681095084825"><a name="p460681095084825"></a><a name="p460681095084825"></a>Declares the standard RTC APIs. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table287555386084825"></a>
<table><thead align="left"><tr id="row1071176183084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1496401363084825"><a name="p1496401363084825"></a><a name="p1496401363084825"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p223400550084825"><a name="p223400550084825"></a><a name="p223400550084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1414689810084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1630951228084825"><a name="p1630951228084825"></a><a name="p1630951228084825"></a><a href="RtcTime.md">RtcTime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p143390097084825"><a name="p143390097084825"></a><a name="p143390097084825"></a>Defines the RTC information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1715540073084825"></a>
<table><thead align="left"><tr id="row1079626414084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1717606609084825"><a name="p1717606609084825"></a><a name="p1717606609084825"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1604186015084825"><a name="p1604186015084825"></a><a name="p1604186015084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row640454030084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1631984539084825"><a name="p1631984539084825"></a><a name="p1631984539084825"></a><a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a>) (enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687111835084825"><a name="p1687111835084825"></a><a name="p1687111835084825"></a>typedef int32_t(*&nbsp;</p>
<p id="p1444070829084825"><a name="p1444070829084825"></a><a name="p1444070829084825"></a>Defines a callback that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1989364932084825"></a>
<table><thead align="left"><tr id="row437761397084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1286798799084825"><a name="p1286798799084825"></a><a name="p1286798799084825"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1480124331084825"><a name="p1480124331084825"></a><a name="p1480124331084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2032073637084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476989345084825"><a name="p476989345084825"></a><a name="p476989345084825"></a><a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> { <a href="RTC.md#ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b">RTC_ALARM_INDEX_A</a> = 0, <a href="RTC.md#ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352">RTC_ALARM_INDEX_B</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990718936084825"><a name="p1990718936084825"></a><a name="p1990718936084825"></a>Enumerates alarm indexes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table333747993084825"></a>
<table><thead align="left"><tr id="row646141468084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p997304253084825"><a name="p997304253084825"></a><a name="p997304253084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p457302345084825"><a name="p457302345084825"></a><a name="p457302345084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1839834741084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p187763380084825"><a name="p187763380084825"></a><a name="p187763380084825"></a><a href="RTC.md#ga3fcf1d7f9bd17c501282a047923161fe">RtcOpen</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005985080084825"><a name="p2005985080084825"></a><a name="p2005985080084825"></a>struct <a href="DevHandle.md">DevHandle</a> *&nbsp;</p>
<p id="p587289421084825"><a name="p587289421084825"></a><a name="p587289421084825"></a>Opens the RTC device to obtain its handle. </p>
</td>
</tr>
<tr id="row1560352500084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p58723705084825"><a name="p58723705084825"></a><a name="p58723705084825"></a><a href="RTC.md#gabbf47f061b0f083066ec1da5bdbad9fe">RtcClose</a> (struct <a href="DevHandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388429066084825"><a name="p388429066084825"></a><a name="p388429066084825"></a>void&nbsp;</p>
<p id="p86395050084825"><a name="p86395050084825"></a><a name="p86395050084825"></a>Releases a specified handle of the RTC device. </p>
</td>
</tr>
<tr id="row2076793393084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1035826774084825"><a name="p1035826774084825"></a><a name="p1035826774084825"></a><a href="RTC.md#gab3049a463cd2d18b098ae267ec4e9f48">RtcReadTime</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964538806084825"><a name="p964538806084825"></a><a name="p964538806084825"></a>int32_t&nbsp;</p>
<p id="p410399279084825"><a name="p410399279084825"></a><a name="p410399279084825"></a>Reads time from the RTC driver. </p>
</td>
</tr>
<tr id="row411661290084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p551523655084825"><a name="p551523655084825"></a><a name="p551523655084825"></a><a href="RTC.md#gaa1bfb39230ba3155d03702ad04af67b4">RtcWriteTime</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, const struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p77686627084825"><a name="p77686627084825"></a><a name="p77686627084825"></a>int32_t&nbsp;</p>
<p id="p1273322850084825"><a name="p1273322850084825"></a><a name="p1273322850084825"></a>Writes format-compliant time to the RTC driver. </p>
</td>
</tr>
<tr id="row1985598702084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1305864466084825"><a name="p1305864466084825"></a><a name="p1305864466084825"></a><a href="RTC.md#ga3a82b2990f646c8bef671ba443691a8a">RtcReadAlarm</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1571268604084825"><a name="p1571268604084825"></a><a name="p1571268604084825"></a>int32_t&nbsp;</p>
<p id="p1338031508084825"><a name="p1338031508084825"></a><a name="p1338031508084825"></a>Reads the RTC alarm time that was set last time. </p>
</td>
</tr>
<tr id="row906514489084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985395579084825"><a name="p1985395579084825"></a><a name="p1985395579084825"></a><a href="RTC.md#gad63c5aafffb1f8bee44497f71de5de8f">RtcWriteAlarm</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, const struct <a href="RtcTime.md">RtcTime</a> *<a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681476493084825"><a name="p1681476493084825"></a><a name="p1681476493084825"></a>int32_t&nbsp;</p>
<p id="p1101954031084825"><a name="p1101954031084825"></a><a name="p1101954031084825"></a>Writes the RTC alarm time based on the alarm index. </p>
</td>
</tr>
<tr id="row1920614130084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1206880570084825"><a name="p1206880570084825"></a><a name="p1206880570084825"></a><a href="RTC.md#gac40e57d996375e1762968b66dedb5914">RtcRegisterAlarmCallback</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, <a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a> cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497600397084825"><a name="p497600397084825"></a><a name="p497600397084825"></a>int32_t&nbsp;</p>
<p id="p438318499084825"><a name="p438318499084825"></a><a name="p438318499084825"></a>Registers <a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a> that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
<tr id="row1165513335084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393930253084825"><a name="p1393930253084825"></a><a name="p1393930253084825"></a><a href="RTC.md#ga9253cd3579500b86caccd67252291259">RtcAlarmInterruptEnable</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, uint8_t enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p762362851084825"><a name="p762362851084825"></a><a name="p762362851084825"></a>int32_t&nbsp;</p>
<p id="p6680044084825"><a name="p6680044084825"></a><a name="p6680044084825"></a>Enables or disables alarm interrupts. </p>
</td>
</tr>
<tr id="row2137901983084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1301562193084825"><a name="p1301562193084825"></a><a name="p1301562193084825"></a><a href="RTC.md#gafde58faab893e2b4c4b2a836985463e7">RtcGetFreq</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint32_t *freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p708319704084825"><a name="p708319704084825"></a><a name="p708319704084825"></a>int32_t&nbsp;</p>
<p id="p1977791454084825"><a name="p1977791454084825"></a><a name="p1977791454084825"></a>Reads the RTC external frequency. </p>
</td>
</tr>
<tr id="row1733579408084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p531424713084825"><a name="p531424713084825"></a><a name="p531424713084825"></a><a href="RTC.md#ga740cb1ef1925f2c3bff31e4cfc83d745">RtcSetFreq</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint32_t freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1371456884084825"><a name="p1371456884084825"></a><a name="p1371456884084825"></a>int32_t&nbsp;</p>
<p id="p221770567084825"><a name="p221770567084825"></a><a name="p221770567084825"></a>Sets the frequency of the external crystal oscillator connected to the RTC driver. </p>
</td>
</tr>
<tr id="row1292745113084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p880643843084825"><a name="p880643843084825"></a><a name="p880643843084825"></a><a href="RTC.md#ga775682fde8d650c958e103832ff63dc9">RtcReset</a> (struct <a href="DevHandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1425464731084825"><a name="p1425464731084825"></a><a name="p1425464731084825"></a>int32_t&nbsp;</p>
<p id="p344578167084825"><a name="p344578167084825"></a><a name="p344578167084825"></a>Resets the RTC driver. </p>
</td>
</tr>
<tr id="row72639917084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p392913715084825"><a name="p392913715084825"></a><a name="p392913715084825"></a><a href="RTC.md#ga94acd2872dda4b0c487da7d106db3d60">RtcReadReg</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint8_t usrDefIndex, uint8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p36312770084825"><a name="p36312770084825"></a><a name="p36312770084825"></a>int32_t&nbsp;</p>
<p id="p1745844428084825"><a name="p1745844428084825"></a><a name="p1745844428084825"></a>Reads the configuration of a custom RTC register based on the register index. </p>
</td>
</tr>
<tr id="row835308699084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616430382084825"><a name="p1616430382084825"></a><a name="p1616430382084825"></a><a href="RTC.md#ga786f9e5a4c2731512c084b86f6f7a3a6">RtcWriteReg</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint8_t usrDefIndex, uint8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902419108084825"><a name="p1902419108084825"></a><a name="p1902419108084825"></a>int32_t&nbsp;</p>
<p id="p618069073084825"><a name="p618069073084825"></a><a name="p618069073084825"></a>Writes the configuration of a custom RTC register based on the register index. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section563580440084825"></a>

## **Typedef Documentation**<a name="section1240407772084825"></a>

## RtcAlarmCallback<a name="gaf9932b7e647bce0503f1314bbe5eef8d"></a>

```
typedef int32_t(* RtcAlarmCallback) (enum [RtcAlarmIndex](RTC.md#gad7b3a575c848e2669db5e5b6f7e74330))
```

 **Description:**

Defines a callback that will be invoked when an alarm is generated at the specified time. 

## **Enumeration Type Documentation**<a name="section1428676745084825"></a>

## RtcAlarmIndex<a name="gad7b3a575c848e2669db5e5b6f7e74330"></a>

```
enum [RtcAlarmIndex](RTC.md#gad7b3a575c848e2669db5e5b6f7e74330)
```

 **Description:**

Enumerates alarm indexes. 

The alarm indexes will be used when you perform operations related to alarms.

<a name="table1933030643084825"></a>
<table><thead align="left"><tr id="row1154492993084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p18076595084825"><a name="p18076595084825"></a><a name="p18076595084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p107752809084825"><a name="p107752809084825"></a><a name="p107752809084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1643615597084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b"><a name="ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b"></a><a name="ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b"></a></strong>RTC_ALARM_INDEX_A&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1159092671084825"><a name="p1159092671084825"></a><a name="p1159092671084825"></a>Index of alarm A </p>
 </td>
</tr>
<tr id="row391152575084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352"><a name="ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352"></a><a name="ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352"></a></strong>RTC_ALARM_INDEX_B&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705460523084825"><a name="p1705460523084825"></a><a name="p1705460523084825"></a>Index of alarm B </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1314279044084825"></a>

## RtcAlarmInterruptEnable\(\)<a name="ga9253cd3579500b86caccd67252291259"></a>

```
int32_t RtcAlarmInterruptEnable (struct [DevHandle](DevHandle.md) * handle, enum [RtcAlarmIndex](RTC.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, uint8_t enable )
```

 **Description:**

Enables or disables alarm interrupts. 

Before performing alarm operations, you need to call this function to enable alarm interrupts, so that the  [RtcRegisterAlarmCallback](RTC.md#gac40e57d996375e1762968b66dedb5914)  will be called when the alarm is not generated upon a timeout.

**Parameters:**

<a name="table1845467557084825"></a>
<table><thead align="left"><tr id="row1248075899084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1831503035084825"><a name="p1831503035084825"></a><a name="p1831503035084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1135357820084825"><a name="p1135357820084825"></a><a name="p1135357820084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1976387995084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b2015938387084825"><a name="b2015938387084825"></a><a name="b2015938387084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row242894764084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row954982304084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">enable</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to enable RTC alarm interrupts. The value <strong id="b1702955231084825"><a name="b1702955231084825"></a><a name="b1702955231084825"></a>1</strong> means to enable alarm interrupts and value <strong id="b537370151084825"><a name="b537370151084825"></a><a name="b537370151084825"></a>0</strong> means to disable alarm interrupts.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcClose\(\)<a name="gabbf47f061b0f083066ec1da5bdbad9fe"></a>

```
void RtcClose (struct [DevHandle](DevHandle.md) * handle)
```

 **Description:**

Releases a specified handle of the RTC device. 

**Parameters:**

<a name="table2121935543084825"></a>
<table><thead align="left"><tr id="row1453737149084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1274275021084825"><a name="p1274275021084825"></a><a name="p1274275021084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1947206240084825"><a name="p1947206240084825"></a><a name="p1947206240084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2104173821084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle to release, which is created via <strong id="b251201914084825"><a name="b251201914084825"></a><a name="b251201914084825"></a>RtcGetHandle</strong>.</td>
</tr>
</tbody>
</table>

## RtcGetFreq\(\)<a name="gafde58faab893e2b4c4b2a836985463e7"></a>

```
int32_t RtcGetFreq (struct [DevHandle](DevHandle.md) * handle, uint32_t * freq )
```

 **Description:**

Reads the RTC external frequency. 

This function reads the frequency of the external crystal oscillator connected to the RTC driver.

**Parameters:**

<a name="table419386933084825"></a>
<table><thead align="left"><tr id="row22183564084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p502730167084825"><a name="p502730167084825"></a><a name="p502730167084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p690995675084825"><a name="p690995675084825"></a><a name="p690995675084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1003500020084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b197628124084825"><a name="b197628124084825"></a><a name="b197628124084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1854065382084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">freq</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the frequency of the external crystal oscillator, in Hz.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcOpen\(\)<a name="ga3fcf1d7f9bd17c501282a047923161fe"></a>

```
struct [DevHandle](DevHandle.md)* RtcOpen (void )
```

 **Description:**

Opens the RTC device to obtain its handle. 

The OS supports only one RTC device.

**Returns:**

Returns  [DevHandle](DevHandle.md)  if the operation is successful; returns  **NULL**  if the operation fails. 



## RtcReadAlarm\(\)<a name="ga3a82b2990f646c8bef671ba443691a8a"></a>

```
int32_t RtcReadAlarm (struct [DevHandle](DevHandle.md) * handle, enum [RtcAlarmIndex](RTC.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, struct [RtcTime](RtcTime.md) * time )
```

 **Description:**

Reads the RTC alarm time that was set last time. 

**Parameters:**

<a name="table1221161410084825"></a>
<table><thead align="left"><tr id="row1152505480084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1583491755084825"><a name="p1583491755084825"></a><a name="p1583491755084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p352258869084825"><a name="p352258869084825"></a><a name="p352258869084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1828994909084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b783277971084825"><a name="b783277971084825"></a><a name="b783277971084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1331037322084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row167494757084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC alarm time information. For details, see <a href="RtcTime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcReadReg\(\)<a name="ga94acd2872dda4b0c487da7d106db3d60"></a>

```
int32_t RtcReadReg (struct [DevHandle](DevHandle.md) * handle, uint8_t usrDefIndex, uint8_t * value )
```

 **Description:**

Reads the configuration of a custom RTC register based on the register index. 

One index corresponds to one byte of the configuration value.

**Parameters:**

<a name="table156965048084825"></a>
<table><thead align="left"><tr id="row1741957483084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2071207024084825"><a name="p2071207024084825"></a><a name="p2071207024084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1562883593084825"><a name="p1562883593084825"></a><a name="p1562883593084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row261172386084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1475417835084825"><a name="b1475417835084825"></a><a name="b1475417835084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1457194237084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">usrDefIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of the custom register. </td>
</tr>
<tr id="row1916599901084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration value of the specified register index.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcReadTime\(\)<a name="gab3049a463cd2d18b098ae267ec4e9f48"></a>

```
int32_t RtcReadTime (struct [DevHandle](DevHandle.md) * handle, struct [RtcTime](RtcTime.md) * time )
```

 **Description:**

Reads time from the RTC driver. 

The time information includes the year, month, day, day of the week, hour, minute, second, and millisecond.

**Parameters:**

<a name="table1687251699084825"></a>
<table><thead align="left"><tr id="row1205120626084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1881901596084825"><a name="p1881901596084825"></a><a name="p1881901596084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p193299915084825"><a name="p193299915084825"></a><a name="p193299915084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1770435177084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1880046505084825"><a name="b1880046505084825"></a><a name="b1880046505084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row814099691084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time information read from the RTC driver. For details, see <a href="RtcTime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcRegisterAlarmCallback\(\)<a name="gac40e57d996375e1762968b66dedb5914"></a>

```
int32_t RtcRegisterAlarmCallback (struct [DevHandle](DevHandle.md) * handle, enum [RtcAlarmIndex](RTC.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, [RtcAlarmCallback](RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d) cb )
```

 **Description:**

Registers  [RtcAlarmCallback](RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d)  that will be invoked when an alarm is generated at the specified time. 

**Parameters:**

<a name="table1365150466084825"></a>
<table><thead align="left"><tr id="row1238602907084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p731532171084825"><a name="p731532171084825"></a><a name="p731532171084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1915422763084825"><a name="p1915422763084825"></a><a name="p1915422763084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1333073132084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1259141714084825"><a name="b1259141714084825"></a><a name="b1259141714084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1409060310084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row1690573715084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to register. For details, see <a href="RTC.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcReset\(\)<a name="ga775682fde8d650c958e103832ff63dc9"></a>

```
int32_t RtcReset (struct [DevHandle](DevHandle.md) * handle)
```

 **Description:**

Resets the RTC driver. 

After the reset, the configuration registers are restored to the default values.

**Parameters:**

<a name="table345732472084825"></a>
<table><thead align="left"><tr id="row1909549609084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1191172054084825"><a name="p1191172054084825"></a><a name="p1191172054084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p938034920084825"><a name="p938034920084825"></a><a name="p938034920084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row548792285084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1574611420084825"><a name="b1574611420084825"></a><a name="b1574611420084825"></a>RtcGetHandle</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcSetFreq\(\)<a name="ga740cb1ef1925f2c3bff31e4cfc83d745"></a>

```
int32_t RtcSetFreq (struct [DevHandle](DevHandle.md) * handle, uint32_t freq )
```

 **Description:**

Sets the frequency of the external crystal oscillator connected to the RTC driver. 

Note that the frequency must be configured in accordance with the requirements specified in the product manual of the in-use component.

**Parameters:**

<a name="table1746819457084825"></a>
<table><thead align="left"><tr id="row1326980682084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1852070912084825"><a name="p1852070912084825"></a><a name="p1852070912084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p58599866084825"><a name="p58599866084825"></a><a name="p58599866084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1836356939084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1445726579084825"><a name="b1445726579084825"></a><a name="b1445726579084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row2118222294084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">freq</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frequency to set for the external crystal oscillator, in Hz.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcWriteAlarm\(\)<a name="gad63c5aafffb1f8bee44497f71de5de8f"></a>

```
int32_t RtcWriteAlarm (struct [DevHandle](DevHandle.md) * handle, enum [RtcAlarmIndex](RTC.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, const struct [RtcTime](RtcTime.md) * time )
```

 **Description:**

Writes the RTC alarm time based on the alarm index. 

Note that the RTC start time is 1970/01/01 Thursday 00:00:00 \(UTC\). Set the maximum value of  **year**  based on the requirements specified in the product manual of the in-use component.

**Parameters:**

<a name="table956675321084825"></a>
<table><thead align="left"><tr id="row377786907084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p273726967084825"><a name="p273726967084825"></a><a name="p273726967084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p644448657084825"><a name="p644448657084825"></a><a name="p644448657084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row855919602084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b115118327084825"><a name="b115118327084825"></a><a name="b115118327084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1317653353084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="RTC.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row809310087084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tm</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC alarm time information. For details, see <a href="RtcTime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcWriteReg\(\)<a name="ga786f9e5a4c2731512c084b86f6f7a3a6"></a>

```
int32_t RtcWriteReg (struct [DevHandle](DevHandle.md) * handle, uint8_t usrDefIndex, uint8_t value )
```

 **Description:**

Writes the configuration of a custom RTC register based on the register index. 

One index corresponds to one byte of the configuration value.

**Parameters:**

<a name="table1614832699084825"></a>
<table><thead align="left"><tr id="row1001928896084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1657487025084825"><a name="p1657487025084825"></a><a name="p1657487025084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2061845272084825"><a name="p2061845272084825"></a><a name="p2061845272084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row430123470084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1642316858084825"><a name="b1642316858084825"></a><a name="b1642316858084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1490872696084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">usrDefIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of the custom register. </td>
</tr>
<tr id="row2134452613084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the configuration value to write at the index of the register.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcWriteTime\(\)<a name="gaa1bfb39230ba3155d03702ad04af67b4"></a>

```
int32_t RtcWriteTime (struct [DevHandle](DevHandle.md) * handle, const struct [RtcTime](RtcTime.md) * time )
```

 **Description:**

Writes format-compliant time to the RTC driver. 

Note that the RTC start time is 1970/01/01 Thursday 00:00:00 \(UTC\). Set the maximum value of  **year**  based on the requirements specified in the product manual of the in-use component.

**Parameters:**

<a name="table1461786879084825"></a>
<table><thead align="left"><tr id="row1362404262084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1292475824084825"><a name="p1292475824084825"></a><a name="p1292475824084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1372512214084825"><a name="p1372512214084825"></a><a name="p1372512214084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1228336108084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1827028853084825"><a name="b1827028853084825"></a><a name="b1827028853084825"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1081118717084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time information to write. For details, see <a href="RtcTime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



