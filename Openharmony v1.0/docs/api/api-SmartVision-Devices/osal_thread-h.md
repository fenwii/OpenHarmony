# osal\_thread.h<a name="ZH-CN_TOPIC_0000001055198106"></a>

## **Overview**<a name="section9295025093526"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Declares thread types and interfaces. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section43698181093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table611031096093526"></a>
<table><thead align="left"><tr id="row473276305093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p777370058093526"><a name="p777370058093526"></a><a name="p777370058093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1223629087093526"><a name="p1223629087093526"></a><a name="p1223629087093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row892515518093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974695945093526"><a name="p1974695945093526"></a><a name="p1974695945093526"></a><a href="OsalThreadParam.md">OsalThreadParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705315551093526"><a name="p705315551093526"></a><a name="p705315551093526"></a>Describes thread parameters. </p>
</td>
</tr>
<tr id="row888579898093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p817031958093526"><a name="p817031958093526"></a><a name="p817031958093526"></a><a href="OsalThread.md">OsalThread</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p646894906093526"><a name="p646894906093526"></a><a name="p646894906093526"></a>Describes a thread. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1495800508093526"></a>
<table><thead align="left"><tr id="row1628840397093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1969196521093526"><a name="p1969196521093526"></a><a name="p1969196521093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1281194796093526"><a name="p1281194796093526"></a><a name="p1281194796093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1468122184093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295389391093526"><a name="p295389391093526"></a><a name="p295389391093526"></a><a href="OSAL.md#ga6178591bdeb64df97a5232350cc9bc26">OSAL_DECLARE_THREAD</a>(thread)&nbsp;&nbsp;&nbsp;struct <a href="OsalThread.md">OsalThread</a> thread</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2026521228093526"><a name="p2026521228093526"></a><a name="p2026521228093526"></a>Defines a thread macro. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1972506493093526"></a>
<table><thead align="left"><tr id="row1128909315093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p781975513093526"><a name="p781975513093526"></a><a name="p781975513093526"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p429538028093526"><a name="p429538028093526"></a><a name="p429538028093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1136926419093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269296807093526"><a name="p269296807093526"></a><a name="p269296807093526"></a><a href="OSAL.md#ga21ea0f87d53e65ec86a424c532d688d8">OsalThreadEntry</a>) (void *)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p834884089093526"><a name="p834884089093526"></a><a name="p834884089093526"></a> typedef int(*&nbsp;</p>
<p id="p1665254889093526"><a name="p1665254889093526"></a><a name="p1665254889093526"></a>Defines a thread callback function type. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1404110867093526"></a>
<table><thead align="left"><tr id="row1363722518093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p708862187093526"><a name="p708862187093526"></a><a name="p708862187093526"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1088449504093526"><a name="p1088449504093526"></a><a name="p1088449504093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1204950302093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500712097093526"><a name="p500712097093526"></a><a name="p500712097093526"></a><a href="OSAL.md#gab8c099a9c39fdde73c74b3f7367be5d0">OSAL_THREAD_PRIORITY</a> { <a href="OSAL.md#ggab8c099a9c39fdde73c74b3f7367be5d0a077e53412997ddef962069a7cea4def6">OSAL_THREAD_PRI_LOW</a>, <a href="OSAL.md#ggab8c099a9c39fdde73c74b3f7367be5d0abc9ef48a9fc95f359a5c4d52041111e5">OSAL_THREAD_PRI_DEFAULT</a>, <a href="OSAL.md#ggab8c099a9c39fdde73c74b3f7367be5d0a61697eda5c5265d6d62271d00c098121">OSAL_THREAD_PRI_HIGH</a>, <a href="OSAL.md#ggab8c099a9c39fdde73c74b3f7367be5d0a9e66435e6d967adc68606b359a8753bd">OSAL_THREAD_PRI_HIGHEST</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954109599093526"><a name="p954109599093526"></a><a name="p954109599093526"></a>Enumerates thread priorities. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2007601846093526"></a>
<table><thead align="left"><tr id="row1568468822093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p759433291093526"><a name="p759433291093526"></a><a name="p759433291093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p631976213093526"><a name="p631976213093526"></a><a name="p631976213093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1883584943093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655100584093526"><a name="p655100584093526"></a><a name="p655100584093526"></a><a href="OSAL.md#gad598b3f4b91f5e6aeeaf7b8a6e507f1e">OsalThreadCreate</a> (struct <a href="OsalThread.md">OsalThread</a> *thread, <a href="OSAL.md#ga21ea0f87d53e65ec86a424c532d688d8">OsalThreadEntry</a> threadEntry, void *entryPara)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472520113093526"><a name="p1472520113093526"></a><a name="p1472520113093526"></a>int32_t&nbsp;</p>
<p id="p1466089539093526"><a name="p1466089539093526"></a><a name="p1466089539093526"></a>Creates a thread. </p>
</td>
</tr>
<tr id="row556515819093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p203594720093526"><a name="p203594720093526"></a><a name="p203594720093526"></a><a href="OSAL.md#ga74c93bd48d27cde830451f63b224307a">OsalThreadStart</a> (struct <a href="OsalThread.md">OsalThread</a> *thread, const struct <a href="OsalThreadParam.md">OsalThreadParam</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430735575093526"><a name="p1430735575093526"></a><a name="p1430735575093526"></a>int32_t&nbsp;</p>
<p id="p665290193093526"><a name="p665290193093526"></a><a name="p665290193093526"></a>Starts a thread. </p>
</td>
</tr>
<tr id="row460134978093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896522237093526"><a name="p1896522237093526"></a><a name="p1896522237093526"></a><a href="OSAL.md#ga223ce6b94770348a93168525c536e6f9">OsalThreadDestroy</a> (struct <a href="OsalThread.md">OsalThread</a> *thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586661374093526"><a name="p1586661374093526"></a><a name="p1586661374093526"></a>int32_t&nbsp;</p>
<p id="p477338347093526"><a name="p477338347093526"></a><a name="p477338347093526"></a>Destroys a thread. </p>
</td>
</tr>
<tr id="row1105140009093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p127887452093526"><a name="p127887452093526"></a><a name="p127887452093526"></a><a href="OSAL.md#gad556075f625d01557c0075a2c092a1da">OsalThreadSuspend</a> (struct <a href="OsalThread.md">OsalThread</a> *thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705661799093526"><a name="p1705661799093526"></a><a name="p1705661799093526"></a>int32_t&nbsp;</p>
<p id="p2032169598093526"><a name="p2032169598093526"></a><a name="p2032169598093526"></a>Suspends a thread. </p>
</td>
</tr>
<tr id="row1989737878093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549197369093526"><a name="p549197369093526"></a><a name="p549197369093526"></a><a href="OSAL.md#ga32f0b5c622518b7453f758d95b137a94">OsalThreadResume</a> (struct <a href="OsalThread.md">OsalThread</a> *thread)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p565019935093526"><a name="p565019935093526"></a><a name="p565019935093526"></a>int32_t&nbsp;</p>
<p id="p781361276093526"><a name="p781361276093526"></a><a name="p781361276093526"></a>Resumes a thread. </p>
</td>
</tr>
</tbody>
</table>

