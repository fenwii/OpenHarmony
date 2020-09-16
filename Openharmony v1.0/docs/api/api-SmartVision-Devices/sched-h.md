# sched.h<a name="ZH-CN_TOPIC_0000001055547982"></a>

## **Overview**<a name="section1674309400084832"></a>

**Related Modules:**

[PROCESS](PROCESS.md)

**Description:**

Provides process- and thread-related structures and functions \(for example, obtaining scheduling policies and parameters\). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2102270390084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table76136569084832"></a>
<table><thead align="left"><tr id="row673019051084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1724456940084832"><a name="p1724456940084832"></a><a name="p1724456940084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p559383879084832"><a name="p559383879084832"></a><a name="p559383879084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row281971899084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094526267084832"><a name="p2094526267084832"></a><a name="p2094526267084832"></a><a href="sched_param.md">sched_param</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p219643089084832"><a name="p219643089084832"></a><a name="p219643089084832"></a>Defines process scheduling parameters. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table726292122084832"></a>
<table><thead align="left"><tr id="row714472971084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2067679953084832"><a name="p2067679953084832"></a><a name="p2067679953084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p883810261084832"><a name="p883810261084832"></a><a name="p883810261084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1041160385084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p974080666084832"><a name="p974080666084832"></a><a name="p974080666084832"></a><a href="PROCESS.md#gafaebd1698caeb9b9b9e614ad84edd609">sched_get_priority_max</a> (int policy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930059467084832"><a name="p1930059467084832"></a><a name="p1930059467084832"></a>int&nbsp;</p>
<p id="p623666001084832"><a name="p623666001084832"></a><a name="p623666001084832"></a>Obtains the maximum static priority that can be used for a process. </p>
</td>
</tr>
<tr id="row400886103084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1351723838084832"><a name="p1351723838084832"></a><a name="p1351723838084832"></a><a href="PROCESS.md#gaf1f370fc36ea6b22ed42b5ee3cf82a81">sched_get_priority_min</a> (int policy)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1788610545084832"><a name="p1788610545084832"></a><a name="p1788610545084832"></a>int&nbsp;</p>
<p id="p76126684084832"><a name="p76126684084832"></a><a name="p76126684084832"></a>Obtains the minimum static priority that can be used for a process. </p>
</td>
</tr>
<tr id="row436561363084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838177490084832"><a name="p838177490084832"></a><a name="p838177490084832"></a><a href="PROCESS.md#ga563c7ac53bac2c1b51379147e66c44ec">sched_getparam</a> (pid_t pid, struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242628305084832"><a name="p1242628305084832"></a><a name="p1242628305084832"></a>int&nbsp;</p>
<p id="p3526901084832"><a name="p3526901084832"></a><a name="p3526901084832"></a>Obtains scheduling parameters of a process. </p>
</td>
</tr>
<tr id="row402593533084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p362326562084832"><a name="p362326562084832"></a><a name="p362326562084832"></a><a href="PROCESS.md#ga99fcb2532b1482d236dc04495a3f194d">sched_getscheduler</a> (pid_t pid)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2136513765084832"><a name="p2136513765084832"></a><a name="p2136513765084832"></a>int&nbsp;</p>
<p id="p1923505825084832"><a name="p1923505825084832"></a><a name="p1923505825084832"></a>Obtains the scheduling policy of a process. </p>
</td>
</tr>
<tr id="row1100941662084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464769697084832"><a name="p1464769697084832"></a><a name="p1464769697084832"></a><a href="PROCESS.md#ga484f0eb93529d29a66e24485725c4c7b">sched_rr_get_interval</a> (pid_t pid, struct <a href="timespec.md">timespec</a> *interval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p771937703084832"><a name="p771937703084832"></a><a name="p771937703084832"></a>int&nbsp;</p>
<p id="p1412945204084832"><a name="p1412945204084832"></a><a name="p1412945204084832"></a>Obtains the execution time limit of a process. </p>
</td>
</tr>
<tr id="row549862058084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424160286084832"><a name="p424160286084832"></a><a name="p424160286084832"></a><a href="PROCESS.md#ga06b497c4ea6bbabd2b62ba1a8a848a1b">sched_setparam</a> (pid_t pid, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p193239513084832"><a name="p193239513084832"></a><a name="p193239513084832"></a>int&nbsp;</p>
<p id="p765545272084832"><a name="p765545272084832"></a><a name="p765545272084832"></a>Sets scheduling parameters related to a scheduling policy for a process. </p>
</td>
</tr>
<tr id="row462179729084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p508209585084832"><a name="p508209585084832"></a><a name="p508209585084832"></a><a href="PROCESS.md#ga84ad29a6f2ad27370df09c664ac65eac">sched_setscheduler</a> (pid_t pid, int policy, const struct <a href="sched_param.md">sched_param</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1599663949084832"><a name="p1599663949084832"></a><a name="p1599663949084832"></a>int&nbsp;</p>
<p id="p469348614084832"><a name="p469348614084832"></a><a name="p469348614084832"></a>Sets a scheduling policy for a process. </p>
</td>
</tr>
<tr id="row1664166845084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620033358084832"><a name="p620033358084832"></a><a name="p620033358084832"></a><a href="PROCESS.md#ga357cd4b34c13011749dfffb42b489f09">sched_yield</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19142245084832"><a name="p19142245084832"></a><a name="p19142245084832"></a>int&nbsp;</p>
<p id="p1200500819084832"><a name="p1200500819084832"></a><a name="p1200500819084832"></a>Yields the running process. </p>
</td>
</tr>
</tbody>
</table>

