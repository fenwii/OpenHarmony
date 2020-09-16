# RTC<a name="EN-US_TOPIC_0000001055039466"></a>

## **Overview**<a name="section413384609093521"></a>

Provides standard real-time clock \(RTC\) APIs. 

These APIs allow you to perform operations such as reading or writing system time, reading or writing alarm time, setting alarm interrupts, registering alarm callbacks, setting the external frequency, resetting the RTC driver, and customizing RTC configurations. The RTC driver provides precise real time for the operating system \(OS\). If the OS is powered off, the RTC driver continues to keep track of the system time using an external battery.

**Since:**

1.0

## **Summary**<a name="section282649754093521"></a>

## Files<a name="files"></a>

<a name="table704414184093521"></a>
<table><thead align="left"><tr id="row1764677613093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1023983285093521"><a name="p1023983285093521"></a><a name="p1023983285093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p589755885093521"><a name="p589755885093521"></a><a name="p589755885093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row898144024093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1654962587093521"><a name="p1654962587093521"></a><a name="p1654962587093521"></a><a href="rtc_if-h.md">rtc_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1726052973093521"><a name="p1726052973093521"></a><a name="p1726052973093521"></a>Declares the standard RTC APIs. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1322328909093521"></a>
<table><thead align="left"><tr id="row128252741093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p633300058093521"><a name="p633300058093521"></a><a name="p633300058093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p702019239093521"><a name="p702019239093521"></a><a name="p702019239093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row586840723093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1696088341093521"><a name="p1696088341093521"></a><a name="p1696088341093521"></a><a href="rtctime.md">RtcTime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p215874222093521"><a name="p215874222093521"></a><a name="p215874222093521"></a>Defines the RTC information. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1051697849093521"></a>
<table><thead align="left"><tr id="row2066230666093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p272333322093521"><a name="p272333322093521"></a><a name="p272333322093521"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p670736132093521"><a name="p670736132093521"></a><a name="p670736132093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row668529916093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1780210016093521"><a name="p1780210016093521"></a><a name="p1780210016093521"></a><em id="gaf9932b7e647bce0503f1314bbe5eef8d"><a name="gaf9932b7e647bce0503f1314bbe5eef8d"></a><a name="gaf9932b7e647bce0503f1314bbe5eef8d"></a></em>RtcAlarmCallback ) (enum <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140309370093521"><a name="p140309370093521"></a><a name="p140309370093521"></a><strong id="b656114973"><a name="b656114973"></a><a name="b656114973"></a></strong> typedef int32_t(* </p>
<p id="p918521637093521"><a name="p918521637093521"></a><a name="p918521637093521"></a>Defines a callback that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1542348730093521"></a>
<table><thead align="left"><tr id="row1869879084093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p7336256093521"><a name="p7336256093521"></a><a name="p7336256093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1492518531093521"><a name="p1492518531093521"></a><a name="p1492518531093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2113321662093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379837811093521"><a name="p1379837811093521"></a><a name="p1379837811093521"></a><a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> { <a href="rtc.md#ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b">RTC_ALARM_INDEX_A</a> = 0, <a href="rtc.md#ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352">RTC_ALARM_INDEX_B</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p819027507093521"><a name="p819027507093521"></a><a name="p819027507093521"></a>Enumerates alarm indexes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table454941123093521"></a>
<table><thead align="left"><tr id="row992707622093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1322875222093521"><a name="p1322875222093521"></a><a name="p1322875222093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p869967716093521"><a name="p869967716093521"></a><a name="p869967716093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1011926722093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p252860186093521"><a name="p252860186093521"></a><a name="p252860186093521"></a><a href="rtc.md#ga3fcf1d7f9bd17c501282a047923161fe">RtcOpen</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1925072324093521"><a name="p1925072324093521"></a><a name="p1925072324093521"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1412189172093521"><a name="p1412189172093521"></a><a name="p1412189172093521"></a>Opens the RTC device to obtain its handle. </p>
</td>
</tr>
<tr id="row439111271093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p287353328093521"><a name="p287353328093521"></a><a name="p287353328093521"></a><a href="rtc.md#gabbf47f061b0f083066ec1da5bdbad9fe">RtcClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p342954698093521"><a name="p342954698093521"></a><a name="p342954698093521"></a>void </p>
<p id="p531356832093521"><a name="p531356832093521"></a><a name="p531356832093521"></a>Releases a specified handle of the RTC device. </p>
</td>
</tr>
<tr id="row434411123093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p379895631093521"><a name="p379895631093521"></a><a name="p379895631093521"></a><a href="rtc.md#gab3049a463cd2d18b098ae267ec4e9f48">RtcReadTime</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="rtctime.md">RtcTime</a> *<a href="en-us_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1605713419093521"><a name="p1605713419093521"></a><a name="p1605713419093521"></a>int32_t </p>
<p id="p334046675093521"><a name="p334046675093521"></a><a name="p334046675093521"></a>Reads time from the RTC driver. </p>
</td>
</tr>
<tr id="row1046218584093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p944073501093521"><a name="p944073501093521"></a><a name="p944073501093521"></a><a href="rtc.md#gaa1bfb39230ba3155d03702ad04af67b4">RtcWriteTime</a> (struct <a href="devhandle.md">DevHandle</a> *handle, const struct <a href="rtctime.md">RtcTime</a> *<a href="en-us_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1240921132093521"><a name="p1240921132093521"></a><a name="p1240921132093521"></a>int32_t </p>
<p id="p413634172093521"><a name="p413634172093521"></a><a name="p413634172093521"></a>Writes format-compliant time to the RTC driver. </p>
</td>
</tr>
<tr id="row922490600093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1184746641093521"><a name="p1184746641093521"></a><a name="p1184746641093521"></a><a href="rtc.md#ga3a82b2990f646c8bef671ba443691a8a">RtcReadAlarm</a> (struct <a href="devhandle.md">DevHandle</a> *handle, enum <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, struct <a href="rtctime.md">RtcTime</a> *<a href="en-us_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1483941894093521"><a name="p1483941894093521"></a><a name="p1483941894093521"></a>int32_t </p>
<p id="p1741757373093521"><a name="p1741757373093521"></a><a name="p1741757373093521"></a>Reads the RTC alarm time that was set last time. </p>
</td>
</tr>
<tr id="row831848830093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1591457611093521"><a name="p1591457611093521"></a><a name="p1591457611093521"></a><a href="rtc.md#gad63c5aafffb1f8bee44497f71de5de8f">RtcWriteAlarm</a> (struct <a href="devhandle.md">DevHandle</a> *handle, enum <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, const struct <a href="rtctime.md">RtcTime</a> *<a href="en-us_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727419872093521"><a name="p727419872093521"></a><a name="p727419872093521"></a>int32_t </p>
<p id="p500970763093521"><a name="p500970763093521"></a><a name="p500970763093521"></a>Writes the RTC alarm time based on the alarm index. </p>
</td>
</tr>
<tr id="row820404879093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p458584345093521"><a name="p458584345093521"></a><a name="p458584345093521"></a><a href="rtc.md#gac40e57d996375e1762968b66dedb5914">RtcRegisterAlarmCallback</a> (struct <a href="devhandle.md">DevHandle</a> *handle, enum <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, <a href="rtc.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a> cb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2115148176093521"><a name="p2115148176093521"></a><a name="p2115148176093521"></a>int32_t </p>
<p id="p944758566093521"><a name="p944758566093521"></a><a name="p944758566093521"></a>Registers <a href="rtc.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a> that will be invoked when an alarm is generated at the specified time. </p>
</td>
</tr>
<tr id="row83290207093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1095240362093521"><a name="p1095240362093521"></a><a name="p1095240362093521"></a><a href="rtc.md#ga9253cd3579500b86caccd67252291259">RtcAlarmInterruptEnable</a> (struct <a href="devhandle.md">DevHandle</a> *handle, enum <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a> alarmIndex, uint8_t enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1667288410093521"><a name="p1667288410093521"></a><a name="p1667288410093521"></a>int32_t </p>
<p id="p1440709771093521"><a name="p1440709771093521"></a><a name="p1440709771093521"></a>Enables or disables alarm interrupts. </p>
</td>
</tr>
<tr id="row563780284093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1073229750093521"><a name="p1073229750093521"></a><a name="p1073229750093521"></a><a href="rtc.md#gafde58faab893e2b4c4b2a836985463e7">RtcGetFreq</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t *freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p641388026093521"><a name="p641388026093521"></a><a name="p641388026093521"></a>int32_t </p>
<p id="p633410747093521"><a name="p633410747093521"></a><a name="p633410747093521"></a>Reads the RTC external frequency. </p>
</td>
</tr>
<tr id="row171157579093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1902000317093521"><a name="p1902000317093521"></a><a name="p1902000317093521"></a><a href="rtc.md#ga740cb1ef1925f2c3bff31e4cfc83d745">RtcSetFreq</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839905874093521"><a name="p839905874093521"></a><a name="p839905874093521"></a>int32_t </p>
<p id="p1681899005093521"><a name="p1681899005093521"></a><a name="p1681899005093521"></a>Sets the frequency of the external crystal oscillator connected to the RTC driver. </p>
</td>
</tr>
<tr id="row1036002330093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396551746093521"><a name="p1396551746093521"></a><a name="p1396551746093521"></a><a href="rtc.md#ga775682fde8d650c958e103832ff63dc9">RtcReset</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644679346093521"><a name="p644679346093521"></a><a name="p644679346093521"></a>int32_t </p>
<p id="p1633084976093521"><a name="p1633084976093521"></a><a name="p1633084976093521"></a>Resets the RTC driver. </p>
</td>
</tr>
<tr id="row1386557013093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1947161351093521"><a name="p1947161351093521"></a><a name="p1947161351093521"></a><a href="rtc.md#ga94acd2872dda4b0c487da7d106db3d60">RtcReadReg</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t usrDefIndex, uint8_t *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182464436093521"><a name="p182464436093521"></a><a name="p182464436093521"></a>int32_t </p>
<p id="p408281511093521"><a name="p408281511093521"></a><a name="p408281511093521"></a>Reads the configuration of a custom RTC register based on the register index. </p>
</td>
</tr>
<tr id="row1691474759093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152831449093521"><a name="p1152831449093521"></a><a name="p1152831449093521"></a><a href="rtc.md#ga786f9e5a4c2731512c084b86f6f7a3a6">RtcWriteReg</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t usrDefIndex, uint8_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1967869605093521"><a name="p1967869605093521"></a><a name="p1967869605093521"></a>int32_t </p>
<p id="p290992327093521"><a name="p290992327093521"></a><a name="p290992327093521"></a>Writes the configuration of a custom RTC register based on the register index. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section242126847093521"></a>

## **Enumeration Type Documentation**<a name="section785151175093521"></a>

## RtcAlarmIndex<a name="gad7b3a575c848e2669db5e5b6f7e74330"></a>

```
enum [RtcAlarmIndex](rtc.md#gad7b3a575c848e2669db5e5b6f7e74330)
```

 **Description:**

Enumerates alarm indexes. 

The alarm indexes will be used when you perform operations related to alarms.

<a name="table1615960987093521"></a>
<table><thead align="left"><tr id="row760863074093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p229590463093521"><a name="p229590463093521"></a><a name="p229590463093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p878731569093521"><a name="p878731569093521"></a><a name="p878731569093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row720006758093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b"><a name="ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b"></a><a name="ggad7b3a575c848e2669db5e5b6f7e74330a4a768788d6e3932637aed682317a7c6b"></a></strong>RTC_ALARM_INDEX_A </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1578376653093521"><a name="p1578376653093521"></a><a name="p1578376653093521"></a>Index of alarm A </p>
 </td>
</tr>
<tr id="row972580826093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352"><a name="ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352"></a><a name="ggad7b3a575c848e2669db5e5b6f7e74330a15a8e9ba8ffd5b1ebf1f8353ca581352"></a></strong>RTC_ALARM_INDEX_B </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1291793693093521"><a name="p1291793693093521"></a><a name="p1291793693093521"></a>Index of alarm B </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section389380468093521"></a>

## RtcAlarmInterruptEnable\(\)<a name="ga9253cd3579500b86caccd67252291259"></a>

```
int32_t RtcAlarmInterruptEnable (struct [DevHandle](devhandle.md) * handle, enum [RtcAlarmIndex](rtc.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, uint8_t enable )
```

 **Description:**

Enables or disables alarm interrupts. 

Before performing alarm operations, you need to call this function to enable alarm interrupts, so that the  [RtcRegisterAlarmCallback](rtc.md#gac40e57d996375e1762968b66dedb5914)  will be called when the alarm is not generated upon a timeout.

**Parameters:**

<a name="table1408051216093521"></a>
<table><thead align="left"><tr id="row1897013525093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2079063377093521"><a name="p2079063377093521"></a><a name="p2079063377093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p295812377093521"><a name="p295812377093521"></a><a name="p295812377093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row19591866093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1025858414093521"><a name="b1025858414093521"></a><a name="b1025858414093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row698007374093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row594440287093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">enable</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to enable RTC alarm interrupts. The value <strong id="b1899126920093521"><a name="b1899126920093521"></a><a name="b1899126920093521"></a>1</strong> means to enable alarm interrupts and value <strong id="b1648433254093521"><a name="b1648433254093521"></a><a name="b1648433254093521"></a>0</strong> means to disable alarm interrupts.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcClose\(\)<a name="gabbf47f061b0f083066ec1da5bdbad9fe"></a>

```
void RtcClose (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Releases a specified handle of the RTC device. 

**Parameters:**

<a name="table204210916093521"></a>
<table><thead align="left"><tr id="row2114646283093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p808114225093521"><a name="p808114225093521"></a><a name="p808114225093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1643229674093521"><a name="p1643229674093521"></a><a name="p1643229674093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2005732189093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle to release, which is created via <strong id="b1796908560093521"><a name="b1796908560093521"></a><a name="b1796908560093521"></a>RtcGetHandle</strong>.</td>
</tr>
</tbody>
</table>

## RtcGetFreq\(\)<a name="gafde58faab893e2b4c4b2a836985463e7"></a>

```
int32_t RtcGetFreq (struct [DevHandle](devhandle.md) * handle, uint32_t * freq )
```

 **Description:**

Reads the RTC external frequency. 

This function reads the frequency of the external crystal oscillator connected to the RTC driver.

**Parameters:**

<a name="table1235265649093521"></a>
<table><thead align="left"><tr id="row300558597093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p224752946093521"><a name="p224752946093521"></a><a name="p224752946093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p952995590093521"><a name="p952995590093521"></a><a name="p952995590093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1265750346093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b277304415093521"><a name="b277304415093521"></a><a name="b277304415093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1319964133093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">freq</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the frequency of the external crystal oscillator, in Hz.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcOpen\(\)<a name="ga3fcf1d7f9bd17c501282a047923161fe"></a>

```
struct [DevHandle](devhandle.md)* RtcOpen (void )
```

 **Description:**

Opens the RTC device to obtain its handle. 

The OS supports only one RTC device.

**Returns:**

Returns  [DevHandle](devhandle.md)  if the operation is successful; returns  **NULL**  if the operation fails. 



## RtcReadAlarm\(\)<a name="ga3a82b2990f646c8bef671ba443691a8a"></a>

```
int32_t RtcReadAlarm (struct [DevHandle](devhandle.md) * handle, enum [RtcAlarmIndex](rtc.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, struct [RtcTime](rtctime.md) * time )
```

 **Description:**

Reads the RTC alarm time that was set last time. 

**Parameters:**

<a name="table162448104093521"></a>
<table><thead align="left"><tr id="row1493472911093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1493605734093521"><a name="p1493605734093521"></a><a name="p1493605734093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p846747868093521"><a name="p846747868093521"></a><a name="p846747868093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1214743885093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b387535997093521"><a name="b387535997093521"></a><a name="b387535997093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row1807708613093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row748033729093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC alarm time information. For details, see <a href="rtctime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcReadReg\(\)<a name="ga94acd2872dda4b0c487da7d106db3d60"></a>

```
int32_t RtcReadReg (struct [DevHandle](devhandle.md) * handle, uint8_t usrDefIndex, uint8_t * value )
```

 **Description:**

Reads the configuration of a custom RTC register based on the register index. 

One index corresponds to one byte of the configuration value.

**Parameters:**

<a name="table368457927093521"></a>
<table><thead align="left"><tr id="row875214868093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p979328003093521"><a name="p979328003093521"></a><a name="p979328003093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1367150434093521"><a name="p1367150434093521"></a><a name="p1367150434093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row802562778093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b155541912093521"><a name="b155541912093521"></a><a name="b155541912093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row432967364093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">usrDefIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of the custom register. </td>
</tr>
<tr id="row1942179495093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration value of the specified register index.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcReadTime\(\)<a name="gab3049a463cd2d18b098ae267ec4e9f48"></a>

```
int32_t RtcReadTime (struct [DevHandle](devhandle.md) * handle, struct [RtcTime](rtctime.md) * time )
```

 **Description:**

Reads time from the RTC driver. 

The time information includes the year, month, day, day of the week, hour, minute, second, and millisecond.

**Parameters:**

<a name="table1282480086093521"></a>
<table><thead align="left"><tr id="row2069334217093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1030216493093521"><a name="p1030216493093521"></a><a name="p1030216493093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p22710908093521"><a name="p22710908093521"></a><a name="p22710908093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1931844786093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1270893308093521"><a name="b1270893308093521"></a><a name="b1270893308093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row25920622093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time information read from the RTC driver. For details, see <a href="rtctime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcRegisterAlarmCallback\(\)<a name="gac40e57d996375e1762968b66dedb5914"></a>

```
int32_t RtcRegisterAlarmCallback (struct [DevHandle](devhandle.md) * handle, enum [RtcAlarmIndex](rtc.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, [RtcAlarmCallback](rtc.md#gaf9932b7e647bce0503f1314bbe5eef8d) cb )
```

 **Description:**

Registers  [RtcAlarmCallback](rtc.md#gaf9932b7e647bce0503f1314bbe5eef8d)  that will be invoked when an alarm is generated at the specified time. 

**Parameters:**

<a name="table1481156665093521"></a>
<table><thead align="left"><tr id="row600043312093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1602367490093521"><a name="p1602367490093521"></a><a name="p1602367490093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p39259559093521"><a name="p39259559093521"></a><a name="p39259559093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1176654135093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b748939600093521"><a name="b748939600093521"></a><a name="b748939600093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row2080741403093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row1662668017093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the callback to register. For details, see <a href="rtc.md#gaf9932b7e647bce0503f1314bbe5eef8d">RtcAlarmCallback</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcReset\(\)<a name="ga775682fde8d650c958e103832ff63dc9"></a>

```
int32_t RtcReset (struct [DevHandle](devhandle.md) * handle)
```

 **Description:**

Resets the RTC driver. 

After the reset, the configuration registers are restored to the default values.

**Parameters:**

<a name="table22778335093521"></a>
<table><thead align="left"><tr id="row1380358810093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1363536303093521"><a name="p1363536303093521"></a><a name="p1363536303093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1354884443093521"><a name="p1354884443093521"></a><a name="p1354884443093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1857614163093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1644655525093521"><a name="b1644655525093521"></a><a name="b1644655525093521"></a>RtcGetHandle</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcSetFreq\(\)<a name="ga740cb1ef1925f2c3bff31e4cfc83d745"></a>

```
int32_t RtcSetFreq (struct [DevHandle](devhandle.md) * handle, uint32_t freq )
```

 **Description:**

Sets the frequency of the external crystal oscillator connected to the RTC driver. 

Note that the frequency must be configured in accordance with the requirements specified in the product manual of the in-use component.

**Parameters:**

<a name="table94452020093521"></a>
<table><thead align="left"><tr id="row375657748093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1370609795093521"><a name="p1370609795093521"></a><a name="p1370609795093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p733546174093521"><a name="p733546174093521"></a><a name="p733546174093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row293457866093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b484295584093521"><a name="b484295584093521"></a><a name="b484295584093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row2075686904093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">freq</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frequency to set for the external crystal oscillator, in Hz.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcWriteAlarm\(\)<a name="gad63c5aafffb1f8bee44497f71de5de8f"></a>

```
int32_t RtcWriteAlarm (struct [DevHandle](devhandle.md) * handle, enum [RtcAlarmIndex](rtc.md#gad7b3a575c848e2669db5e5b6f7e74330) alarmIndex, const struct [RtcTime](rtctime.md) * time )
```

 **Description:**

Writes the RTC alarm time based on the alarm index. 

Note that the RTC start time is 1970/01/01 Thursday 00:00:00 \(UTC\). Set the maximum value of  **year**  based on the requirements specified in the product manual of the in-use component.

**Parameters:**

<a name="table189517181093521"></a>
<table><thead align="left"><tr id="row1568251987093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2112482406093521"><a name="p2112482406093521"></a><a name="p2112482406093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1226669856093521"><a name="p1226669856093521"></a><a name="p1226669856093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row823916756093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b2131610602093521"><a name="b2131610602093521"></a><a name="b2131610602093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row837193087093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alarmIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the RTC alarm index. For details, see <a href="rtc.md#gad7b3a575c848e2669db5e5b6f7e74330">RtcAlarmIndex</a>. </td>
</tr>
<tr id="row906199917093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tm</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC alarm time information. For details, see <a href="rtctime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcWriteReg\(\)<a name="ga786f9e5a4c2731512c084b86f6f7a3a6"></a>

```
int32_t RtcWriteReg (struct [DevHandle](devhandle.md) * handle, uint8_t usrDefIndex, uint8_t value )
```

 **Description:**

Writes the configuration of a custom RTC register based on the register index. 

One index corresponds to one byte of the configuration value.

**Parameters:**

<a name="table1643532640093521"></a>
<table><thead align="left"><tr id="row938207764093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2074153280093521"><a name="p2074153280093521"></a><a name="p2074153280093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p286519964093521"><a name="p286519964093521"></a><a name="p286519964093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row363417556093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b1190980416093521"><a name="b1190980416093521"></a><a name="b1190980416093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row2015441742093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">usrDefIndex</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index of the custom register. </td>
</tr>
<tr id="row881078034093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the configuration value to write at the index of the register.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



## RtcWriteTime\(\)<a name="gaa1bfb39230ba3155d03702ad04af67b4"></a>

```
int32_t RtcWriteTime (struct [DevHandle](devhandle.md) * handle, const struct [RtcTime](rtctime.md) * time )
```

 **Description:**

Writes format-compliant time to the RTC driver. 

Note that the RTC start time is 1970/01/01 Thursday 00:00:00 \(UTC\). Set the maximum value of  **year**  based on the requirements specified in the product manual of the in-use component.

**Parameters:**

<a name="table110039299093521"></a>
<table><thead align="left"><tr id="row1067714704093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p179576997093521"><a name="p179576997093521"></a><a name="p179576997093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p158172035093521"><a name="p158172035093521"></a><a name="p158172035093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1178085783093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the RTC device handle, which is obtained via <strong id="b2092319530093521"><a name="b2092319530093521"></a><a name="b2092319530093521"></a>RtcGetHandle</strong>. </td>
</tr>
<tr id="row514929124093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">time</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time information to write. For details, see <a href="rtctime.md">RtcTime</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value if the operation fails. For details, see  [HDF\_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67). 



