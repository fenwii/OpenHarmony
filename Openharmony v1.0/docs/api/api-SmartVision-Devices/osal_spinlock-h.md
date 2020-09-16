# osal\_spinlock.h<a name="ZH-CN_TOPIC_0000001054879508"></a>

## **Overview**<a name="section464676111093526"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Declares spinlock types and interfaces. 

This file provides the interfaces for initializing, destroying, obtaining, and releasing a spinlock, the interfaces for obtaining a spinlock and disabling the interrupt request \(IRQ\), releasing a spinlock and enabling the IRQ, obtaining a spinlock, disabling the IRQ, and saving its status, and releasing a spinlock, enabling the IRQ, and restoring the saved IRQ status. The spinlock needs to be destroyed when it is no longer used.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1703050601093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1320705234093526"></a>
<table><thead align="left"><tr id="row273362796093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1255401266093526"><a name="p1255401266093526"></a><a name="p1255401266093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p649238167093526"><a name="p649238167093526"></a><a name="p649238167093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1906890913093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492270181093526"><a name="p1492270181093526"></a><a name="p1492270181093526"></a><a href="OsalSpinlock.md">OsalSpinlock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1815746979093526"><a name="p1815746979093526"></a><a name="p1815746979093526"></a>Describes a spinlock. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1209159646093526"></a>
<table><thead align="left"><tr id="row12864627093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p943434641093526"><a name="p943434641093526"></a><a name="p943434641093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1997370342093526"><a name="p1997370342093526"></a><a name="p1997370342093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row469706952093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826105816093526"><a name="p1826105816093526"></a><a name="p1826105816093526"></a><a href="OSAL.md#gad624af1547135d60073f38b7f31ad826">OSAL_DECLARE_SPINLOCK</a>(spinlock)&nbsp;&nbsp;&nbsp;<a href="OsalSpinlock.md">OsalSpinlock</a> spinlock</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p607975608093526"><a name="p607975608093526"></a><a name="p607975608093526"></a>Defines a spinlock. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table682634799093526"></a>
<table><thead align="left"><tr id="row703514785093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1516891485093526"><a name="p1516891485093526"></a><a name="p1516891485093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p21530869093526"><a name="p21530869093526"></a><a name="p21530869093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1746761159093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302156945093526"><a name="p1302156945093526"></a><a name="p1302156945093526"></a><a href="OSAL.md#gae36a2d6e4e0191273c9f86a918befb5c">OsalSpinInit</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p894625414093526"><a name="p894625414093526"></a><a name="p894625414093526"></a>int32_t&nbsp;</p>
<p id="p1634898011093526"><a name="p1634898011093526"></a><a name="p1634898011093526"></a>Initializes a spinlock. </p>
</td>
</tr>
<tr id="row1281386595093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453570783093526"><a name="p1453570783093526"></a><a name="p1453570783093526"></a><a href="OSAL.md#gacd3824f292ddef395bd1a4a7b5546470">OsalSpinDestroy</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504315068093526"><a name="p504315068093526"></a><a name="p504315068093526"></a>int32_t&nbsp;</p>
<p id="p1438591379093526"><a name="p1438591379093526"></a><a name="p1438591379093526"></a>Destroys a spinlock. </p>
</td>
</tr>
<tr id="row999944949093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p490635849093526"><a name="p490635849093526"></a><a name="p490635849093526"></a><a href="OSAL.md#gae1c4b9ac8ea2a4820d73c20ae017dbd7">OsalSpinLock</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p637415324093526"><a name="p637415324093526"></a><a name="p637415324093526"></a>int32_t&nbsp;</p>
<p id="p761569176093526"><a name="p761569176093526"></a><a name="p761569176093526"></a>Obtains a spinlock. </p>
</td>
</tr>
<tr id="row615488617093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1014766380093526"><a name="p1014766380093526"></a><a name="p1014766380093526"></a><a href="OSAL.md#gada1f1826b19dc900af370a2bcd9681b9">OsalSpinUnlock</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p872172745093526"><a name="p872172745093526"></a><a name="p872172745093526"></a>int32_t&nbsp;</p>
<p id="p1722301422093526"><a name="p1722301422093526"></a><a name="p1722301422093526"></a>Releases a spinlock. </p>
</td>
</tr>
<tr id="row1830842665093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2129152489093526"><a name="p2129152489093526"></a><a name="p2129152489093526"></a><a href="OSAL.md#ga7d409ec573a06078112a8ffae14afce5">OsalSpinLockIrq</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1719855838093526"><a name="p1719855838093526"></a><a name="p1719855838093526"></a>int32_t&nbsp;</p>
<p id="p1809359729093526"><a name="p1809359729093526"></a><a name="p1809359729093526"></a>Obtains a spinlock and disables the IRQ. </p>
</td>
</tr>
<tr id="row1603919016093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755511847093526"><a name="p1755511847093526"></a><a name="p1755511847093526"></a><a href="OSAL.md#ga7d7848d572fbda413b3b5770e95a234e">OsalSpinUnlockIrq</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319628186093526"><a name="p319628186093526"></a><a name="p319628186093526"></a>int32_t&nbsp;</p>
<p id="p1102998770093526"><a name="p1102998770093526"></a><a name="p1102998770093526"></a>Releases a spinlock and enables the IRQ. </p>
</td>
</tr>
<tr id="row1414742086093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p443490086093526"><a name="p443490086093526"></a><a name="p443490086093526"></a><a href="OSAL.md#gab711d8d56055e78dd85f84bc530a4d3f">OsalSpinLockIrqSave</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock, uint32_t *flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p612439828093526"><a name="p612439828093526"></a><a name="p612439828093526"></a>int32_t&nbsp;</p>
<p id="p737093664093526"><a name="p737093664093526"></a><a name="p737093664093526"></a>Obtains a spinlock, disables the IRQ, and saves its status. </p>
</td>
</tr>
<tr id="row98480372093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1300439337093526"><a name="p1300439337093526"></a><a name="p1300439337093526"></a><a href="OSAL.md#ga3be4dbde6c9ae740b012e49ab90e7a8a">OsalSpinUnlockIrqRestore</a> (<a href="OsalSpinlock.md">OsalSpinlock</a> *spinlock, uint32_t *flags)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1652979599093526"><a name="p1652979599093526"></a><a name="p1652979599093526"></a>int32_t&nbsp;</p>
<p id="p861202380093526"><a name="p861202380093526"></a><a name="p861202380093526"></a>Releases a spinlock, enables the IRQ, and restores the saved IRQ status. </p>
</td>
</tr>
</tbody>
</table>

