# select.h<a name="EN-US_TOPIC_0000001055069410"></a>

## **Overview**<a name="section95414566084832"></a>

**Related Modules:**

[IO](io.md)

**Description:**

Provides functions and structures related to I/O multiplexing. 

These functions can be used to implement I/O multiplexing.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section811891486084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1545254613084832"></a>
<table><thead align="left"><tr id="row1649408500084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2014026377084832"><a name="p2014026377084832"></a><a name="p2014026377084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1253704069084832"><a name="p1253704069084832"></a><a name="p1253704069084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row492029554084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643407967084832"><a name="p1643407967084832"></a><a name="p1643407967084832"></a><a href="fd_set.md">fd_set</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715559974084832"><a name="p1715559974084832"></a><a name="p1715559974084832"></a>Defines a file descriptor set. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1978641703084832"></a>
<table><thead align="left"><tr id="row921533866084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p701959697084832"><a name="p701959697084832"></a><a name="p701959697084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1731968878084832"><a name="p1731968878084832"></a><a name="p1731968878084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1108902339084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650812497084832"><a name="p1650812497084832"></a><a name="p1650812497084832"></a><a href="io.md#ga86c5dbf5a99358e288f573d6a1e0873f">FD_SETSIZE</a>   1024</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139773375084832"><a name="p1139773375084832"></a><a name="p1139773375084832"></a>Defines the size of <strong id="b1362503161084832"><a name="b1362503161084832"></a><a name="b1362503161084832"></a><a href="fd_set.md">fd_set</a></strong>, that is, the maximum number of monitored files. </p>
</td>
</tr>
<tr id="row861560833084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1661715575084832"><a name="p1661715575084832"></a><a name="p1661715575084832"></a><a href="io.md#ga92ab86a10f942411365b9078833559f0">FD_ZERO</a>(s)   do { int __i; unsigned long *__b=(s)-&gt;fds_bits; for(__i=sizeof (<a href="fd_set.md">fd_set</a>)/sizeof (long); __i; __i--) *__b++=0; } while(0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p80140664084832"><a name="p80140664084832"></a><a name="p80140664084832"></a>Clears all elements in the file descriptor set. </p>
</td>
</tr>
<tr id="row416051624084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1156997731084832"><a name="p1156997731084832"></a><a name="p1156997731084832"></a><a href="io.md#gaa7701be461ce602ff7043cbd898a0c53">FD_SET</a>(d, s)   ((s)-&gt;fds_bits[(d)/(8*sizeof(long))] |= (1UL&lt;&lt;((d)%(8*sizeof(long)))))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1257310763084832"><a name="p1257310763084832"></a><a name="p1257310763084832"></a>Adds a file descriptor to a set. </p>
</td>
</tr>
<tr id="row1677640319084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1913874416084832"><a name="p1913874416084832"></a><a name="p1913874416084832"></a><a href="io.md#ga60efc4a969e971f91b7a73bcace62e58">FD_CLR</a>(d, s)   ((s)-&gt;fds_bits[(d)/(8*sizeof(long))] &amp;= ~(1UL&lt;&lt;((d)%(8*sizeof(long)))))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1222205870084832"><a name="p1222205870084832"></a><a name="p1222205870084832"></a>Removes a file descriptor from a set. </p>
</td>
</tr>
<tr id="row1110544797084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649021908084832"><a name="p649021908084832"></a><a name="p649021908084832"></a><a href="io.md#ga99a3a0e4d7d1d3eb7be68f37554c0a30">FD_ISSET</a>(d, s)   !!((s)-&gt;fds_bits[(d)/(8*sizeof(long))] &amp; (1UL&lt;&lt;((d)%(8*sizeof(long)))))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p477531023084832"><a name="p477531023084832"></a><a name="p477531023084832"></a>Checks whether a file descriptor is in a set. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table919414243084832"></a>
<table><thead align="left"><tr id="row1468911401084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p528750822084832"><a name="p528750822084832"></a><a name="p528750822084832"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2134898350084832"><a name="p2134898350084832"></a><a name="p2134898350084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row308483391084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315107899084832"><a name="p1315107899084832"></a><a name="p1315107899084832"></a><a href="io.md#gaf78c256e09db7de8ea18def79fc5e6b2">fd_mask</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802709091084832"><a name="p1802709091084832"></a><a name="p1802709091084832"></a> typedef unsigned long </p>
<p id="p1625605073084832"><a name="p1625605073084832"></a><a name="p1625605073084832"></a>Defines <strong id="b1857725745084832"><a name="b1857725745084832"></a><a name="b1857725745084832"></a><a href="fd_set.md">fd_set</a></strong> as the alias of the element type. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1202708861084832"></a>
<table><thead align="left"><tr id="row1240106929084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p473382419084832"><a name="p473382419084832"></a><a name="p473382419084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p294226086084832"><a name="p294226086084832"></a><a name="p294226086084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2136086266084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1234837647084832"><a name="p1234837647084832"></a><a name="p1234837647084832"></a><a href="io.md#gaf916439863bed6ba92594e390c227c7e">select</a> (int nfds, <a href="fd_set.md">fd_set</a> *__restrict readfds, <a href="fd_set.md">fd_set</a> *__restrict writefds, <a href="fd_set.md">fd_set</a> *__restrict exceptfds, struct <a href="timeval.md">timeval</a> *__restrict timeout)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p154469654084832"><a name="p154469654084832"></a><a name="p154469654084832"></a>int </p>
<p id="p311161381084832"><a name="p311161381084832"></a><a name="p311161381084832"></a>Monitors the I/O events of multiple file descriptors. </p>
</td>
</tr>
</tbody>
</table>

