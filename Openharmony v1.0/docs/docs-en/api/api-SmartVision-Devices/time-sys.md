# TIME-SYS<a name="EN-US_TOPIC_0000001054748003"></a>

## **Overview**<a name="section1617025998084825"></a>

Provides time-related structures and functions. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section573057091084825"></a>

## Files<a name="files"></a>

<a name="table825798367084825"></a>
<table><thead align="left"><tr id="row192266033084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p281060842084825"><a name="p281060842084825"></a><a name="p281060842084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p637352577084825"><a name="p637352577084825"></a><a name="p637352577084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1126027299084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106420225084825"><a name="p106420225084825"></a><a name="p106420225084825"></a><a href="time-h.md">time.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2058398998084825"><a name="p2058398998084825"></a><a name="p2058398998084825"></a>Provides structures and functions related to the system time. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table110265378084825"></a>
<table><thead align="left"><tr id="row1198783983084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1678700962084825"><a name="p1678700962084825"></a><a name="p1678700962084825"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p318765907084825"><a name="p318765907084825"></a><a name="p318765907084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2032316635084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772240382084825"><a name="p1772240382084825"></a><a name="p1772240382084825"></a><a href="timeval.md">timeval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1233136180084825"><a name="p1233136180084825"></a><a name="p1233136180084825"></a>Describes a period of time, accurate to microseconds. </p>
</td>
</tr>
<tr id="row1671024393084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935917371084825"><a name="p935917371084825"></a><a name="p935917371084825"></a><a href="timespec.md">timespec</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p502340297084825"><a name="p502340297084825"></a><a name="p502340297084825"></a>Describes a period of time, accurate to nanoseconds. </p>
</td>
</tr>
<tr id="row1408615150084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697548861084825"><a name="p697548861084825"></a><a name="p697548861084825"></a><a href="itimerval.md">itimerval</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p398326615084825"><a name="p398326615084825"></a><a name="p398326615084825"></a>Describes a timer. </p>
</td>
</tr>
<tr id="row273398965084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176454503084825"><a name="p176454503084825"></a><a name="p176454503084825"></a><a href="timezone.md">timezone</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p534996797084825"><a name="p534996797084825"></a><a name="p534996797084825"></a>Describes a time zone. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table2127522567084825"></a>
<table><thead align="left"><tr id="row354212481084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p889477735084825"><a name="p889477735084825"></a><a name="p889477735084825"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p176366868084825"><a name="p176366868084825"></a><a name="p176366868084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row913285298084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p614423692084825"><a name="p614423692084825"></a><a name="p614423692084825"></a><em id="gace5b149f36c4133045c32d756e2b9a82"><a name="gace5b149f36c4133045c32d756e2b9a82"></a><a name="gace5b149f36c4133045c32d756e2b9a82"></a></em>ITIMER_REAL    0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p590867262084825"><a name="p590867262084825"></a><a name="p590867262084825"></a>Defines the timer that runs in real time. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1069374872084825"></a>
<table><thead align="left"><tr id="row1327413087084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1628064872084825"><a name="p1628064872084825"></a><a name="p1628064872084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1344928813084825"><a name="p1344928813084825"></a><a name="p1344928813084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row780566616084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313326500084825"><a name="p1313326500084825"></a><a name="p1313326500084825"></a><a href="time-sys.md#ga5ef4514eca25b6c6b73c5a54b8bc9e2b">gettimeofday</a> (struct <a href="timeval.md">timeval</a> *__restrict value, void *__restrict ovalue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619759575084825"><a name="p1619759575084825"></a><a name="p1619759575084825"></a>int </p>
<p id="p549403834084825"><a name="p549403834084825"></a><a name="p549403834084825"></a>Obtains the system time and time zone. </p>
</td>
</tr>
<tr id="row1476296576084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1334998215084825"><a name="p1334998215084825"></a><a name="p1334998215084825"></a><a href="time-sys.md#ga87cde44d5a31b1524f925d980c959985">getitimer</a> (int w, struct <a href="itimerval.md">itimerval</a> *old)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994400571084825"><a name="p1994400571084825"></a><a name="p1994400571084825"></a>int </p>
<p id="p397925961084825"><a name="p397925961084825"></a><a name="p397925961084825"></a>Obtains the value of an intermittent timer. </p>
</td>
</tr>
<tr id="row1500423706084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498304946084825"><a name="p498304946084825"></a><a name="p498304946084825"></a><a href="time-sys.md#ga81245d77d2f570933cc81f13a101bff8">setitimer</a> (int w, const struct <a href="itimerval.md">itimerval</a> *__restrict value, struct <a href="itimerval.md">itimerval</a> *__restrict ovalue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854510192084825"><a name="p854510192084825"></a><a name="p854510192084825"></a>int </p>
<p id="p1973114522084825"><a name="p1973114522084825"></a><a name="p1973114522084825"></a>Sets the value for a timer. </p>
</td>
</tr>
<tr id="row1451724982084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2078376698084825"><a name="p2078376698084825"></a><a name="p2078376698084825"></a><a href="time-sys.md#ga6e6617fc349ed4777425d667ff250fa7">settimeofday</a> (const struct <a href="timeval.md">timeval</a> *tv, const struct <a href="timezone.md">timezone</a> *tz)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883048061084825"><a name="p1883048061084825"></a><a name="p1883048061084825"></a>int </p>
<p id="p1660625993084825"><a name="p1660625993084825"></a><a name="p1660625993084825"></a>Sets the system time and time zone. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1052435599084825"></a>

## **Function Documentation**<a name="section732278707084825"></a>

## getitimer\(\)<a name="ga87cde44d5a31b1524f925d980c959985"></a>

```
int getitimer (int w, struct [itimerval](itimerval.md) * old )
```

 **Description:**

Obtains the value of an intermittent timer. 

**Parameters:**

<a name="table1245527340084825"></a>
<table><thead align="left"><tr id="row430070198084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1017941395084825"><a name="p1017941395084825"></a><a name="p1017941395084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1218417076084825"><a name="p1218417076084825"></a><a name="p1218417076084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1066156706084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">w</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer type. Only <a href="time-sys.md#gace5b149f36c4133045c32d756e2b9a82">ITIMER_REAL</a> is supported. </td>
</tr>
<tr id="row1189108372084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">old</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer value. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1395555288084825"></a>
<table><thead align="left"><tr id="row1258296409084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1145039964084825"><a name="p1145039964084825"></a><a name="p1145039964084825"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1615727535084825"><a name="p1615727535084825"></a><a name="p1615727535084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1527306109084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376636081084825"><a name="p1376636081084825"></a><a name="p1376636081084825"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p850019798084825"><a name="p850019798084825"></a><a name="p850019798084825"></a>Incorrect input or timer type. </p>
</td>
</tr>
</tbody>
</table>

## gettimeofday\(\)<a name="ga5ef4514eca25b6c6b73c5a54b8bc9e2b"></a>

```
int gettimeofday (struct [timeval](timeval.md) *__restrict value, void *__restrict ovalue )
```

 **Description:**

Obtains the system time and time zone. 

**Parameters:**

<a name="table286326577084825"></a>
<table><thead align="left"><tr id="row1596036796084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p393365129084825"><a name="p393365129084825"></a><a name="p393365129084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1259338566084825"><a name="p1259338566084825"></a><a name="p1259338566084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row584004683084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <strong id="b764036135084825"><a name="b764036135084825"></a><a name="b764036135084825"></a>timeval</strong> structure that contains the time. </td>
</tr>
<tr id="row527445636084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ovalue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">This parameter is used for compatibility only. </td>
</tr>
</tbody>
</table>

**Attention:**

Currently, there is no time zone structure. The return value of  **ovalue**  is empty. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table641979477084825"></a>
<table><thead align="left"><tr id="row1111404798084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p720701527084825"><a name="p720701527084825"></a><a name="p720701527084825"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2028863164084825"><a name="p2028863164084825"></a><a name="p2028863164084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row988637233084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280346866084825"><a name="p280346866084825"></a><a name="p280346866084825"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2095748546084825"><a name="p2095748546084825"></a><a name="p2095748546084825"></a>Incorrect input. </p>
</td>
</tr>
</tbody>
</table>

## setitimer\(\)<a name="ga81245d77d2f570933cc81f13a101bff8"></a>

```
int setitimer (int w, const struct [itimerval](itimerval.md) *__restrict value, struct [itimerval](itimerval.md) *__restrict ovalue )
```

 **Description:**

Sets the value for a timer. 

**Parameters:**

<a name="table952016986084825"></a>
<table><thead align="left"><tr id="row1653251937084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1900786889084825"><a name="p1900786889084825"></a><a name="p1900786889084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1020031589084825"><a name="p1020031589084825"></a><a name="p1020031589084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row420722515084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">w</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the timer type. Currently, only <a href="time-sys.md#gace5b149f36c4133045c32d756e2b9a82">ITIMER_REAL</a> is supported. </td>
</tr>
<tr id="row685371915084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the timer value to set. </td>
</tr>
<tr id="row643035268084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ovalue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the original timer value before the current setting, which can be <strong id="b1369295471084825"><a name="b1369295471084825"></a><a name="b1369295471084825"></a>NULL</strong>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table2117263212084825"></a>
<table><thead align="left"><tr id="row1582451809084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1134317088084825"><a name="p1134317088084825"></a><a name="p1134317088084825"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1064401294084825"><a name="p1064401294084825"></a><a name="p1064401294084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row969443180084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2112150985084825"><a name="p2112150985084825"></a><a name="p2112150985084825"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989868443084825"><a name="p1989868443084825"></a><a name="p1989868443084825"></a>Incorrect input or timer type. </p>
</td>
</tr>
</tbody>
</table>

## settimeofday\(\)<a name="ga6e6617fc349ed4777425d667ff250fa7"></a>

```
int settimeofday (const struct [timeval](timeval.md) * tv, const struct [timezone](timezone.md) * tz )
```

 **Description:**

Sets the system time and time zone. 

**Parameters:**

<a name="table613435389084825"></a>
<table><thead align="left"><tr id="row169668102084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1953545329084825"><a name="p1953545329084825"></a><a name="p1953545329084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p874517521084825"><a name="p874517521084825"></a><a name="p874517521084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row626945386084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tv</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time to set. </td>
</tr>
<tr id="row253178761084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tz</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the time zone to set. This parameter is not used yet. </td>
</tr>
</tbody>
</table>

**Attention:**

**tz**  is invalid. The time is set internally using  **clock\_settime**. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table678334731084825"></a>
<table><thead align="left"><tr id="row1924991776084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1769644581084825"><a name="p1769644581084825"></a><a name="p1769644581084825"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1227878334084825"><a name="p1227878334084825"></a><a name="p1227878334084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row408770764084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p466449714084825"><a name="p466449714084825"></a><a name="p466449714084825"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370213637084825"><a name="p370213637084825"></a><a name="p370213637084825"></a>Incorrect input. </p>
</td>
</tr>
</tbody>
</table>

