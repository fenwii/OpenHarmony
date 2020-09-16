# time.h<a name="EN-US_TOPIC_0000001055189451"></a>

## **Overview**<a name="section1045884953084833"></a>

**Related Modules:**

[TIME](time.md)

**Description:**

Provides time-related structures and functions. 

You can perform time-related management operations, including obtaining and setting broken-down time and system ticks, and manipulating timers.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1430225650084833"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1879695844084833"></a>
<table><thead align="left"><tr id="row1416858993084833"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1921359064084833"><a name="p1921359064084833"></a><a name="p1921359064084833"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1603961170084833"><a name="p1603961170084833"></a><a name="p1603961170084833"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1236607643084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115772675084833"><a name="p2115772675084833"></a><a name="p2115772675084833"></a><a href="tm.md">tm</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032190992084833"><a name="p1032190992084833"></a><a name="p1032190992084833"></a>Describes date and time information. </p>
</td>
</tr>
<tr id="row1459634578084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p285637126084833"><a name="p285637126084833"></a><a name="p285637126084833"></a><a href="itimerspec.md">itimerspec</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71672542084833"><a name="p71672542084833"></a><a name="p71672542084833"></a>Sets a timer. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1424741063084833"></a>
<table><thead align="left"><tr id="row226075607084833"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298375533084833"><a name="p1298375533084833"></a><a name="p1298375533084833"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1623207436084833"><a name="p1623207436084833"></a><a name="p1623207436084833"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1260954665084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1583887074084833"><a name="p1583887074084833"></a><a name="p1583887074084833"></a><a href="time.md#ga922ce1ae64374c9410c8a999e25e82af">CLOCK_REALTIME</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2130806261084833"><a name="p2130806261084833"></a><a name="p2130806261084833"></a>Defines the clock that runs in real time. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table128097152084833"></a>
<table><thead align="left"><tr id="row2127795210084833"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1679768829084833"><a name="p1679768829084833"></a><a name="p1679768829084833"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1586650808084833"><a name="p1586650808084833"></a><a name="p1586650808084833"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row744467936084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p405868913084833"><a name="p405868913084833"></a><a name="p405868913084833"></a><a href="time.md#gae7841e681c8c9d59818568d39553642c">time</a> (time_t *t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p335918744084833"><a name="p335918744084833"></a><a name="p335918744084833"></a>time_t </p>
<p id="p873682121084833"><a name="p873682121084833"></a><a name="p873682121084833"></a>Obtains the time. </p>
</td>
</tr>
<tr id="row1175202708084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1287224579084833"><a name="p1287224579084833"></a><a name="p1287224579084833"></a><a href="time.md#ga1901c00eb89e8e35ea193c6a4676679c">difftime</a> (time_t time1, time_t time2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504412544084833"><a name="p504412544084833"></a><a name="p504412544084833"></a>double </p>
<p id="p2133202596084833"><a name="p2133202596084833"></a><a name="p2133202596084833"></a>Calculates the difference between two times, in seconds. </p>
</td>
</tr>
<tr id="row1948987661084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p626639912084833"><a name="p626639912084833"></a><a name="p626639912084833"></a><a href="time.md#gafc0e3f373a3ea00b37714f1b621ae0b1">mktime</a> (struct <a href="tm.md">tm</a> *<a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720641199084833"><a name="p1720641199084833"></a><a name="p1720641199084833"></a>time_t </p>
<p id="p988394579084833"><a name="p988394579084833"></a><a name="p988394579084833"></a>Converts the broken-down time in the <a href="tm.md">tm</a> structure into seconds. </p>
</td>
</tr>
<tr id="row1697864044084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p201850114084833"><a name="p201850114084833"></a><a name="p201850114084833"></a><a href="time.md#gab94643a711fc91727b668553d4a8806b">strftime</a> (char *restrict s, size_t n, const char *restrict f, const struct <a href="tm.md">tm</a> *restrict <a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p689552928084833"><a name="p689552928084833"></a><a name="p689552928084833"></a>size_t </p>
<p id="p539590001084833"><a name="p539590001084833"></a><a name="p539590001084833"></a>Converts the broken-down time in the <a href="tm.md">tm</a> structure to a string in the required format. </p>
</td>
</tr>
<tr id="row1600869625084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p937720418084833"><a name="p937720418084833"></a><a name="p937720418084833"></a><a href="time.md#ga30d9732f32117a94652e28512905bfb9">gmtime</a> (const time_t *t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1299801235084833"><a name="p1299801235084833"></a><a name="p1299801235084833"></a>struct <a href="tm.md">tm</a> * </p>
<p id="p1922087111084833"><a name="p1922087111084833"></a><a name="p1922087111084833"></a>Converts the number of seconds to the UTC time in the <a href="tm.md">tm</a> structure. </p>
</td>
</tr>
<tr id="row1732902152084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p666812569084833"><a name="p666812569084833"></a><a name="p666812569084833"></a><a href="time.md#ga70311f8aa60fc5ebbd76c55ea10bc899">localtime</a> (const time_t *t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1685060956084833"><a name="p1685060956084833"></a><a name="p1685060956084833"></a>struct <a href="tm.md">tm</a> * </p>
<p id="p973692487084833"><a name="p973692487084833"></a><a name="p973692487084833"></a>Converts the number of seconds to the local time in the <a href="tm.md">tm</a> structure. </p>
</td>
</tr>
<tr id="row852503185084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1481272888084833"><a name="p1481272888084833"></a><a name="p1481272888084833"></a><a href="time.md#ga416a0a99a5bab4c030e93d21152727f4">asctime</a> (const struct <a href="tm.md">tm</a> *<a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p192471159084833"><a name="p192471159084833"></a><a name="p192471159084833"></a>char * </p>
<p id="p965565046084833"><a name="p965565046084833"></a><a name="p965565046084833"></a>Converts the broken-down time in the <a href="tm.md">tm</a> structure into a string. </p>
</td>
</tr>
<tr id="row1780682744084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1928852658084833"><a name="p1928852658084833"></a><a name="p1928852658084833"></a><a href="time.md#ga6e58d33339fabd469b2f4790b0f2b843">ctime</a> (const time_t *timep)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027961494084833"><a name="p1027961494084833"></a><a name="p1027961494084833"></a>char * </p>
<p id="p1754419744084833"><a name="p1754419744084833"></a><a name="p1754419744084833"></a>Converts the date and time into a string. </p>
</td>
</tr>
<tr id="row1178196290084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1051434420084833"><a name="p1051434420084833"></a><a name="p1051434420084833"></a><a href="time.md#ga74c011f36d0ad959f0312dec8a5c8dc8">strftime_l</a> (char *__restrict s, size_t n, const char *__restrict f, const struct <a href="tm.md">tm</a> *__restrict <a href="tm.md">tm</a>, locale_t loc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1340949346084833"><a name="p1340949346084833"></a><a name="p1340949346084833"></a>size_t </p>
<p id="p561670882084833"><a name="p561670882084833"></a><a name="p561670882084833"></a>Converts the broken-down time in the <a href="tm.md">tm</a> structure to a string in a specified programming language and format. </p>
</td>
</tr>
<tr id="row1501674988084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2113139999084833"><a name="p2113139999084833"></a><a name="p2113139999084833"></a><a href="time.md#ga91bb7adea9b0b36acde8dba3012c01a5">gmtime_r</a> (const time_t *__restrict t, struct <a href="tm.md">tm</a> *__restrict <a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1816043298084833"><a name="p1816043298084833"></a><a name="p1816043298084833"></a>struct <a href="tm.md">tm</a> * </p>
<p id="p1981885690084833"><a name="p1981885690084833"></a><a name="p1981885690084833"></a>Converts the number of seconds to the UTC time in the <a href="tm.md">tm</a> structure. (This function is reentrant.) </p>
</td>
</tr>
<tr id="row1757301112084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p233747609084833"><a name="p233747609084833"></a><a name="p233747609084833"></a><a href="time.md#gad8c4ed240ddbd645502ac2f0a306aee0">localtime_r</a> (const time_t *__restrict t, struct <a href="tm.md">tm</a> *__restrict <a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1270070498084833"><a name="p1270070498084833"></a><a name="p1270070498084833"></a>struct <a href="tm.md">tm</a> * </p>
<p id="p331945873084833"><a name="p331945873084833"></a><a name="p331945873084833"></a>Converts the number of seconds to the local time in the <a href="tm.md">tm</a> structure. (This function is reentrant.) </p>
</td>
</tr>
<tr id="row1969486437084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1552900474084833"><a name="p1552900474084833"></a><a name="p1552900474084833"></a><a href="time.md#ga8eb1bca8a6fdc63173a83f1c8cb28e15">asctime_r</a> (const struct <a href="tm.md">tm</a> *__restrict <a href="tm.md">tm</a>, char *__restrict buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1907672065084833"><a name="p1907672065084833"></a><a name="p1907672065084833"></a>char * </p>
<p id="p715288157084833"><a name="p715288157084833"></a><a name="p715288157084833"></a>Converts the broken-down time in the <a href="tm.md">tm</a> structure into a string. (This function is reentrant.) </p>
</td>
</tr>
<tr id="row379250684084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p756167071084833"><a name="p756167071084833"></a><a name="p756167071084833"></a><a href="time.md#gae6eed522503f70a5cf05be0be558b125">ctime_r</a> (const time_t *t, char *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644036176084833"><a name="p644036176084833"></a><a name="p644036176084833"></a>char * </p>
<p id="p1907773236084833"><a name="p1907773236084833"></a><a name="p1907773236084833"></a>Converts the date and time into a string. (This function is reentrant.) </p>
</td>
</tr>
<tr id="row1894202442084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1706488976084833"><a name="p1706488976084833"></a><a name="p1706488976084833"></a><a href="time.md#gafbe0e411e8bf89275e7cd46d0aeedc4b">nanosleep</a> (const struct <a href="timespec.md">timespec</a> *tspec1, struct <a href="timespec.md">timespec</a> *tspec2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327982435084833"><a name="p1327982435084833"></a><a name="p1327982435084833"></a>int </p>
<p id="p657130923084833"><a name="p657130923084833"></a><a name="p657130923084833"></a>Pauses the current thread until a specified time arrives. </p>
</td>
</tr>
<tr id="row1264982463084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p828619647084833"><a name="p828619647084833"></a><a name="p828619647084833"></a><a href="time.md#ga822b364014350d2d70bbd0ccaab1f476">clock_getres</a> (clockid_t id, struct <a href="timespec.md">timespec</a> *tspec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1092222339084833"><a name="p1092222339084833"></a><a name="p1092222339084833"></a>int </p>
<p id="p1838807363084833"><a name="p1838807363084833"></a><a name="p1838807363084833"></a>Obtains the precision of a clock. </p>
</td>
</tr>
<tr id="row1677239083084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1498621129084833"><a name="p1498621129084833"></a><a name="p1498621129084833"></a><a href="time.md#ga28ec1219021575a4b9a7c502b2e9a72c">clock_gettime</a> (clockid_t id, struct <a href="timespec.md">timespec</a> *tspec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459012608084833"><a name="p1459012608084833"></a><a name="p1459012608084833"></a>int </p>
<p id="p764395998084833"><a name="p764395998084833"></a><a name="p764395998084833"></a>Obtains the time of a clock. </p>
</td>
</tr>
<tr id="row1765759674084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p456641230084833"><a name="p456641230084833"></a><a name="p456641230084833"></a><a href="time.md#ga04dbb6f7216d70a1b206741564d4d0fb">clock_settime</a> (clockid_t id, const struct <a href="timespec.md">timespec</a> *tspec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1457064573084833"><a name="p1457064573084833"></a><a name="p1457064573084833"></a>int </p>
<p id="p1796335426084833"><a name="p1796335426084833"></a><a name="p1796335426084833"></a>Sets the time for a clock. </p>
</td>
</tr>
<tr id="row1174702151084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p974236201084833"><a name="p974236201084833"></a><a name="p974236201084833"></a><a href="time.md#ga23d3356807a1cb25b5f64651c4aa7d33">clock_nanosleep</a> (clockid_t id, int flag, const struct <a href="timespec.md">timespec</a> *tspec1, struct <a href="timespec.md">timespec</a> *tspec2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1975203084833"><a name="p1975203084833"></a><a name="p1975203084833"></a>int </p>
<p id="p96072650084833"><a name="p96072650084833"></a><a name="p96072650084833"></a>Pauses the current thread until a specified time of a clock arrives. </p>
</td>
</tr>
<tr id="row948755157084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382872271084833"><a name="p1382872271084833"></a><a name="p1382872271084833"></a><a href="time.md#gaf7dce9c851a2e1a65aaf818b95487431">timer_create</a> (clockid_t id, struct <a href="sigevent.md">sigevent</a> *__restrict evp, timer_t *__restrict t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611484192084833"><a name="p611484192084833"></a><a name="p611484192084833"></a>int </p>
<p id="p146155714084833"><a name="p146155714084833"></a><a name="p146155714084833"></a>Creates a timer for the process. </p>
</td>
</tr>
<tr id="row1119528588084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p55440186084833"><a name="p55440186084833"></a><a name="p55440186084833"></a><a href="time.md#ga61fa078bdadbd957cfcdfb12d0592ac1">timer_delete</a> (timer_t t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1490726931084833"><a name="p1490726931084833"></a><a name="p1490726931084833"></a>int </p>
<p id="p422144154084833"><a name="p422144154084833"></a><a name="p422144154084833"></a>Deletes a timer for the process. </p>
</td>
</tr>
<tr id="row553321109084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1983122191084833"><a name="p1983122191084833"></a><a name="p1983122191084833"></a><a href="time.md#gade973e87fffe05aed7f1e97c1d15178e">timer_settime</a> (timer_t t, int flags, const struct <a href="itimerspec.md">itimerspec</a> *__restrict val, struct <a href="itimerspec.md">itimerspec</a> *__restrict old)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181512725084833"><a name="p181512725084833"></a><a name="p181512725084833"></a>int </p>
<p id="p1677736084084833"><a name="p1677736084084833"></a><a name="p1677736084084833"></a>Sets a timer for the process. </p>
</td>
</tr>
<tr id="row297179298084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p133333058084833"><a name="p133333058084833"></a><a name="p133333058084833"></a><a href="time.md#ga8f65c6a88588c951e0b11629e56714a4">timer_gettime</a> (timer_t t, struct <a href="itimerspec.md">itimerspec</a> *tspec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101809402084833"><a name="p1101809402084833"></a><a name="p1101809402084833"></a>int </p>
<p id="p1182180651084833"><a name="p1182180651084833"></a><a name="p1182180651084833"></a>Obtains a timer of the process. </p>
</td>
</tr>
<tr id="row1810397199084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395813310084833"><a name="p1395813310084833"></a><a name="p1395813310084833"></a><a href="time.md#ga6ecdedfd7f417a3d93aa7a18ff0ac582">timer_getoverrun</a> (timer_t t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844705167084833"><a name="p1844705167084833"></a><a name="p1844705167084833"></a>int </p>
<p id="p548316654084833"><a name="p548316654084833"></a><a name="p548316654084833"></a>Obtains the number of times that a timer overruns. </p>
</td>
</tr>
<tr id="row1121782344084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549619148084833"><a name="p549619148084833"></a><a name="p549619148084833"></a><a href="time.md#ga8454b83c5b4fb93a9dcdd72ab586de22">strptime</a> (const char *s, const char *format, struct <a href="tm.md">tm</a> *<a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p462246137084833"><a name="p462246137084833"></a><a name="p462246137084833"></a>char * </p>
<p id="p1568983494084833"><a name="p1568983494084833"></a><a name="p1568983494084833"></a>Converts a time string to the broken-down time in the <a href="tm.md">tm</a> structure. </p>
</td>
</tr>
<tr id="row25605991084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838613038084833"><a name="p1838613038084833"></a><a name="p1838613038084833"></a><a href="time.md#gae85b268128fa533b20949464ce34165a">getdate</a> (const char *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1992782862084833"><a name="p1992782862084833"></a><a name="p1992782862084833"></a>struct <a href="tm.md">tm</a> * </p>
<p id="p379003829084833"><a name="p379003829084833"></a><a name="p379003829084833"></a>Converts a time string to the broken-down time in the <a href="tm.md">tm</a> structure. </p>
</td>
</tr>
<tr id="row471331326084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1641541792084833"><a name="p1641541792084833"></a><a name="p1641541792084833"></a><a href="time.md#ga69f8377385b2eeee376712dc9f0e3f71">stime</a> (const time_t *t)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1125428143084833"><a name="p1125428143084833"></a><a name="p1125428143084833"></a>int </p>
<p id="p1283576088084833"><a name="p1283576088084833"></a><a name="p1283576088084833"></a>Sets the system time. </p>
</td>
</tr>
<tr id="row1762734127084833"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1764455483084833"><a name="p1764455483084833"></a><a name="p1764455483084833"></a><a href="time.md#ga4fd5240e99b2a9bf19bc0fe39f6ffc07">timegm</a> (struct <a href="tm.md">tm</a> *<a href="tm.md">tm</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175945663084833"><a name="p175945663084833"></a><a name="p175945663084833"></a>time_t </p>
<p id="p913013201084833"><a name="p913013201084833"></a><a name="p913013201084833"></a>Converts the broken-down time in the <a href="tm.md">tm</a> structure to the number of seconds. </p>
</td>
</tr>
</tbody>
</table>

