# RTC Overview<a name="EN-US_TOPIC_0000001051778226"></a>

## Introduction<a name="section104842041574"></a>

The real-time clock \(RTC\) driver provides precise real time for the operating system \(OS\). If the OS is powered off, the RTC driver continues to keep track of the system time using an external battery.

## Available APIs<a name="section16892932155715"></a>

**Table  1**  APIs provided by the RTC driver

<a name="table1731550155318"></a>
<table><thead align="left"><tr id="row4419501537"><th class="cellrowborder" valign="top" width="21.902190219021904%" id="mcps1.2.4.1.1"><p id="p641050105320"><a name="p641050105320"></a><a name="p641050105320"></a><strong id="b17744818255"><a name="b17744818255"></a><a name="b17744818255"></a>Capability</strong></p>
</th>
<th class="cellrowborder" valign="top" width="24.98249824982498%" id="mcps1.2.4.1.2"><p id="p54150165315"><a name="p54150165315"></a><a name="p54150165315"></a><strong id="b257315114254"><a name="b257315114254"></a><a name="b257315114254"></a>Function</strong></p>
</th>
<th class="cellrowborder" valign="top" width="53.11531153115312%" id="mcps1.2.4.1.3"><p id="p941150145313"><a name="p941150145313"></a><a name="p941150145313"></a><strong id="b384185962317"><a name="b384185962317"></a><a name="b384185962317"></a>Description</strong></p>
</th>
</tr>
</thead>
<tbody><tr id="row17550163418501"><td class="cellrowborder" rowspan="2" valign="top" width="21.902190219021904%" headers="mcps1.2.4.1.1 "><p id="p11670643205012"><a name="p11670643205012"></a><a name="p11670643205012"></a>RTC handle</p>
</td>
<td class="cellrowborder" valign="top" width="24.98249824982498%" headers="mcps1.2.4.1.2 "><p id="p16550143465015"><a name="p16550143465015"></a><a name="p16550143465015"></a>RtcOpen</p>
</td>
<td class="cellrowborder" valign="top" width="53.11531153115312%" headers="mcps1.2.4.1.3 "><p id="p9550103415015"><a name="p9550103415015"></a><a name="p9550103415015"></a>Opens the RTC device to obtain its handle.</p>
</td>
</tr>
<tr id="row1879052755020"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1479062716506"><a name="p1479062716506"></a><a name="p1479062716506"></a>RtcClose</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1579142745012"><a name="p1579142745012"></a><a name="p1579142745012"></a>Releases a specified handle of the RTC device.</p>
</td>
</tr>
<tr id="row34145016535"><td class="cellrowborder" rowspan="2" valign="top" width="21.902190219021904%" headers="mcps1.2.4.1.1 "><p id="p229610227124"><a name="p229610227124"></a><a name="p229610227124"></a>RTC time</p>
</td>
<td class="cellrowborder" valign="top" width="24.98249824982498%" headers="mcps1.2.4.1.2 "><p id="p19389143041518"><a name="p19389143041518"></a><a name="p19389143041518"></a>RtcReadTime</p>
</td>
<td class="cellrowborder" valign="top" width="53.11531153115312%" headers="mcps1.2.4.1.3 "><p id="p8738101941716"><a name="p8738101941716"></a><a name="p8738101941716"></a>Reads time information from the RTC driver, including the year, month, the day of the week, day, hour, minute, second, and millisecond.</p>
</td>
</tr>
<tr id="row5632152611414"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p143890309153"><a name="p143890309153"></a><a name="p143890309153"></a>RtcWriteTime</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p573815197171"><a name="p573815197171"></a><a name="p573815197171"></a>Writes time information from the RTC driver, including the year, month, the day of the week, day, hour, minute, second, and millisecond.</p>
</td>
</tr>
<tr id="row1468016592416"><td class="cellrowborder" rowspan="4" valign="top" width="21.902190219021904%" headers="mcps1.2.4.1.1 "><p id="p36817591648"><a name="p36817591648"></a><a name="p36817591648"></a>RTC alarm</p>
</td>
<td class="cellrowborder" valign="top" width="24.98249824982498%" headers="mcps1.2.4.1.2 "><p id="p968116598418"><a name="p968116598418"></a><a name="p968116598418"></a>RtcReadAlarm</p>
</td>
<td class="cellrowborder" valign="top" width="53.11531153115312%" headers="mcps1.2.4.1.3 "><p id="p768110592416"><a name="p768110592416"></a><a name="p768110592416"></a>Reads the RTC alarm time that was set last time.</p>
</td>
</tr>
<tr id="row19313155514"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p73141951155"><a name="p73141951155"></a><a name="p73141951155"></a>RtcWriteAlarm</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p15314656511"><a name="p15314656511"></a><a name="p15314656511"></a>Writes the RTC alarm time based on the alarm index.</p>
</td>
</tr>
<tr id="row138283422555"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2829142165513"><a name="p2829142165513"></a><a name="p2829142165513"></a>RtcRegisterAlarmCallback</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p118291242155518"><a name="p118291242155518"></a><a name="p118291242155518"></a>Registers <strong id="b1648234343210"><a name="b1648234343210"></a><a name="b1648234343210"></a>RtcAlarmCallback</strong> that will be invoked when an alarm is generated at the specified time.</p>
</td>
</tr>
<tr id="row13344113914568"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p2344103915616"><a name="p2344103915616"></a><a name="p2344103915616"></a>RtcAlarmInterruptEnable</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p034415397565"><a name="p034415397565"></a><a name="p034415397565"></a>Enables or disables RTC alarm interrupts.</p>
</td>
</tr>
<tr id="row11801203517565"><td class="cellrowborder" rowspan="3" valign="top" width="21.902190219021904%" headers="mcps1.2.4.1.1 "><p id="p17261458942"><a name="p17261458942"></a><a name="p17261458942"></a>RTC configuration</p>
</td>
<td class="cellrowborder" valign="top" width="24.98249824982498%" headers="mcps1.2.4.1.2 "><p id="p15801153515561"><a name="p15801153515561"></a><a name="p15801153515561"></a>RtcGetFreq</p>
</td>
<td class="cellrowborder" valign="top" width="53.11531153115312%" headers="mcps1.2.4.1.3 "><p id="p980133515566"><a name="p980133515566"></a><a name="p980133515566"></a>Reads the frequency of the external crystal oscillator connected to the RTC driver.</p>
</td>
</tr>
<tr id="row111502322563"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1615073225618"><a name="p1615073225618"></a><a name="p1615073225618"></a>RtcSetFreq</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p10150832165613"><a name="p10150832165613"></a><a name="p10150832165613"></a>Sets the frequency of the external crystal oscillator connected to the RTC driver.</p>
</td>
</tr>
<tr id="row21771259145618"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1717725916562"><a name="p1717725916562"></a><a name="p1717725916562"></a>RtcReset</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p517712598569"><a name="p517712598569"></a><a name="p517712598569"></a>Resets the RTC.</p>
</td>
</tr>
<tr id="row917116425716"><td class="cellrowborder" rowspan="2" valign="top" width="21.902190219021904%" headers="mcps1.2.4.1.1 "><p id="p144765201754"><a name="p144765201754"></a><a name="p144765201754"></a>Custom register</p>
</td>
<td class="cellrowborder" valign="top" width="24.98249824982498%" headers="mcps1.2.4.1.2 "><p id="p1117110418570"><a name="p1117110418570"></a><a name="p1117110418570"></a>RtcReadReg</p>
</td>
<td class="cellrowborder" valign="top" width="53.11531153115312%" headers="mcps1.2.4.1.3 "><p id="p1517114410578"><a name="p1517114410578"></a><a name="p1517114410578"></a>Reads the configuration of a custom RTC register based on the register index.</p>
</td>
</tr>
<tr id="row46738190576"><td class="cellrowborder" valign="top" headers="mcps1.2.4.1.1 "><p id="p1567331910573"><a name="p1567331910573"></a><a name="p1567331910573"></a>RtcWriteReg</p>
</td>
<td class="cellrowborder" valign="top" headers="mcps1.2.4.1.2 "><p id="p1967391913576"><a name="p1967391913576"></a><a name="p1967391913576"></a>Writes the configuration of a custom RTC register based on the register index.</p>
</td>
</tr>
</tbody>
</table>

>![](public_sys-resources/icon-note.gif) **NOTE:** 
>All functions provided in this document can be called only in kernel mode.

