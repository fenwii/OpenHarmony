# osal\_atomic.h<a name="EN-US_TOPIC_0000001054598135"></a>

## **Overview**<a name="section1962658702093526"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Declares atomic and bit operation interfaces. 

This file provides interfaces such as reading and setting an atomic, incrementing and decrementing an atomic counter by 1. This file also provides interfaces such as checking the bit status of a variable, and setting and clearing the bit value of a variable.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section461010256093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table679169468093526"></a>
<table><thead align="left"><tr id="row1338054508093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p980601506093526"><a name="p980601506093526"></a><a name="p980601506093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p331825489093526"><a name="p331825489093526"></a><a name="p331825489093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row268950270093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1661457213093526"><a name="p1661457213093526"></a><a name="p1661457213093526"></a><a href="osalatomic.md">OsalAtomic</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711760343093526"><a name="p711760343093526"></a><a name="p711760343093526"></a>Describes an atomic. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1052373421093526"></a>
<table><thead align="left"><tr id="row995974505093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1426385206093526"><a name="p1426385206093526"></a><a name="p1426385206093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p429674590093526"><a name="p429674590093526"></a><a name="p429674590093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row128766215093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220413136093526"><a name="p220413136093526"></a><a name="p220413136093526"></a><a href="osal.md#gaf7b7a860f5cf11bda3008ce16a5d79d5">OsalAtomicRead</a> (const <a href="osalatomic.md">OsalAtomic</a> *v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807273760093526"><a name="p807273760093526"></a><a name="p807273760093526"></a>int32_t </p>
<p id="p1895685561093526"><a name="p1895685561093526"></a><a name="p1895685561093526"></a>Reads the counter of an atomic. </p>
</td>
</tr>
<tr id="row451256711093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146871937093526"><a name="p2146871937093526"></a><a name="p2146871937093526"></a><a href="osal.md#ga0b82ac10305c7ec5ae46707034b866c3">OsalAtomicSet</a> (<a href="osalatomic.md">OsalAtomic</a> *v, int32_t counter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p653653948093526"><a name="p653653948093526"></a><a name="p653653948093526"></a>void </p>
<p id="p1602625859093526"><a name="p1602625859093526"></a><a name="p1602625859093526"></a>Sets the counter for an atomic. </p>
</td>
</tr>
<tr id="row1790664492093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2096074260093526"><a name="p2096074260093526"></a><a name="p2096074260093526"></a><a href="osal.md#ga11214c11a9b875cb8ba0a67aeccc6ac9">OsalAtomicInc</a> (<a href="osalatomic.md">OsalAtomic</a> *v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510607219093526"><a name="p1510607219093526"></a><a name="p1510607219093526"></a>void </p>
<p id="p80220869093526"><a name="p80220869093526"></a><a name="p80220869093526"></a>Increments the counter of an atomic by 1. </p>
</td>
</tr>
<tr id="row1050298352093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1569945402093526"><a name="p1569945402093526"></a><a name="p1569945402093526"></a><a href="osal.md#gaa411f380e6b21c8467260030ceee38ff">OsalAtomicDec</a> (<a href="osalatomic.md">OsalAtomic</a> *v)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p460123128093526"><a name="p460123128093526"></a><a name="p460123128093526"></a>void </p>
<p id="p706032327093526"><a name="p706032327093526"></a><a name="p706032327093526"></a>Decrements the counter of an atomic by 1. </p>
</td>
</tr>
<tr id="row595636791093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259669543093526"><a name="p1259669543093526"></a><a name="p1259669543093526"></a><a href="osal.md#gaf02c15a3593cac4add3f661b63aebf81">OsalTestBit</a> (unsigned long nr, const volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623372717093526"><a name="p623372717093526"></a><a name="p623372717093526"></a>int32_t </p>
<p id="p1910442073093526"><a name="p1910442073093526"></a><a name="p1910442073093526"></a>Tests the value of a specified bit of a variable. </p>
</td>
</tr>
<tr id="row348853465093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p886374556093526"><a name="p886374556093526"></a><a name="p886374556093526"></a><a href="osal.md#gac0ff99812a327a4a595802a23b41b46f">OsalTestSetBit</a> (unsigned long nr, volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382542873093526"><a name="p382542873093526"></a><a name="p382542873093526"></a>int32_t </p>
<p id="p1020896176093526"><a name="p1020896176093526"></a><a name="p1020896176093526"></a>Sets the value of a specified bit of the variable and returns the bit value before the setting. </p>
</td>
</tr>
<tr id="row1236485997093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p532779354093526"><a name="p532779354093526"></a><a name="p532779354093526"></a><a href="osal.md#ga8665e70c704921f443fd2db8193ff7cc">OsalTestClearBit</a> (unsigned long nr, volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2109435516093526"><a name="p2109435516093526"></a><a name="p2109435516093526"></a>int32_t </p>
<p id="p991058896093526"><a name="p991058896093526"></a><a name="p991058896093526"></a>Clears the value of a specified bit of the variable and returns the bit value before clearing. </p>
</td>
</tr>
<tr id="row1433974472093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1537470943093526"><a name="p1537470943093526"></a><a name="p1537470943093526"></a><a href="osal.md#gae3e5b84f326aa1a2c4b8427509f80cd9">OsalClearBit</a> (unsigned long nr, volatile unsigned long *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149971234093526"><a name="p149971234093526"></a><a name="p149971234093526"></a>void </p>
<p id="p1905362498093526"><a name="p1905362498093526"></a><a name="p1905362498093526"></a>Clears the value of a specified bit of the variable. </p>
</td>
</tr>
</tbody>
</table>

