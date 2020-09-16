# time.h<a name="ZH-CN_TOPIC_0000001055547984"></a>

## **Overview**<a name="section575894279084832"></a>

**Related Modules:**

[TIME-SYS](TIME-SYS.md)

**Description:**

Provides structures and functions related to the system time. 

You can read and write the system time and set timers.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section716891384084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table988896557084832"></a>
<table><thead align="left"><tr id="row2072488565084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1267295866084832"><a name="p1267295866084832"></a><a name="p1267295866084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1035446789084832"><a name="p1035446789084832"></a><a name="p1035446789084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1845438625084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1036911116084832"><a name="p1036911116084832"></a><a name="p1036911116084832"></a><a href="timeval.md">timeval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124173339084832"><a name="p2124173339084832"></a><a name="p2124173339084832"></a>Describes a period of time, accurate to microseconds. </p>
</td>
</tr>
<tr id="row512635500084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1318927027084832"><a name="p1318927027084832"></a><a name="p1318927027084832"></a><a href="timespec.md">timespec</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895072897084832"><a name="p1895072897084832"></a><a name="p1895072897084832"></a>Describes a period of time, accurate to nanoseconds. </p>
</td>
</tr>
<tr id="row218453844084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1429593792084832"><a name="p1429593792084832"></a><a name="p1429593792084832"></a><a href="itimerval.md">itimerval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521516706084832"><a name="p1521516706084832"></a><a name="p1521516706084832"></a>Describes a timer. </p>
</td>
</tr>
<tr id="row1057170779084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p71907745084832"><a name="p71907745084832"></a><a name="p71907745084832"></a><a href="timezone.md">timezone</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946138989084832"><a name="p946138989084832"></a><a name="p946138989084832"></a>Describes a time zone. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1312828559084832"></a>
<table><thead align="left"><tr id="row1638649462084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p502454457084832"><a name="p502454457084832"></a><a name="p502454457084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p280481405084832"><a name="p280481405084832"></a><a name="p280481405084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row425767486084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931176849084832"><a name="p1931176849084832"></a><a name="p1931176849084832"></a><a href="TIME-SYS.md#gace5b149f36c4133045c32d756e2b9a82">ITIMER_REAL</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1909000683084832"><a name="p1909000683084832"></a><a name="p1909000683084832"></a>Defines the timer that runs in real time. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2118607968084832"></a>
<table><thead align="left"><tr id="row260210382084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p131539716084832"><a name="p131539716084832"></a><a name="p131539716084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p27125333084832"><a name="p27125333084832"></a><a name="p27125333084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1614877333084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356985093084832"><a name="p1356985093084832"></a><a name="p1356985093084832"></a><a href="TIME-SYS.md#ga5ef4514eca25b6c6b73c5a54b8bc9e2b">gettimeofday</a> (struct <a href="timeval.md">timeval</a> *__restrict value, void *__restrict ovalue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1136882288084832"><a name="p1136882288084832"></a><a name="p1136882288084832"></a>int&nbsp;</p>
<p id="p1600280072084832"><a name="p1600280072084832"></a><a name="p1600280072084832"></a>Obtains the system time and time zone. </p>
</td>
</tr>
<tr id="row1291984060084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p510232766084832"><a name="p510232766084832"></a><a name="p510232766084832"></a><a href="TIME-SYS.md#ga87cde44d5a31b1524f925d980c959985">getitimer</a> (int w, struct <a href="itimerval.md">itimerval</a> *old)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p487290662084832"><a name="p487290662084832"></a><a name="p487290662084832"></a>int&nbsp;</p>
<p id="p91642063084832"><a name="p91642063084832"></a><a name="p91642063084832"></a>Obtains the value of an intermittent timer. </p>
</td>
</tr>
<tr id="row1498149126084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p840586799084832"><a name="p840586799084832"></a><a name="p840586799084832"></a><a href="TIME-SYS.md#ga81245d77d2f570933cc81f13a101bff8">setitimer</a> (int w, const struct <a href="itimerval.md">itimerval</a> *__restrict value, struct <a href="itimerval.md">itimerval</a> *__restrict ovalue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p719744689084832"><a name="p719744689084832"></a><a name="p719744689084832"></a>int&nbsp;</p>
<p id="p2109922241084832"><a name="p2109922241084832"></a><a name="p2109922241084832"></a>Sets the value for a timer. </p>
</td>
</tr>
<tr id="row275040571084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1569296156084832"><a name="p1569296156084832"></a><a name="p1569296156084832"></a><a href="TIME-SYS.md#ga6e6617fc349ed4777425d667ff250fa7">settimeofday</a> (const struct <a href="timeval.md">timeval</a> *tv, const struct <a href="timezone.md">timezone</a> *tz)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2128186362084832"><a name="p2128186362084832"></a><a name="p2128186362084832"></a>int&nbsp;</p>
<p id="p2117065329084832"><a name="p2117065329084832"></a><a name="p2117065329084832"></a>Sets the system time and time zone. </p>
</td>
</tr>
</tbody>
</table>

