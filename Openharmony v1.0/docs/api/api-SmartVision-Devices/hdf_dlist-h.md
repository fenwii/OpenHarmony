# hdf\_dlist.h<a name="ZH-CN_TOPIC_0000001054598129"></a>

## **Overview**<a name="section1777330021093525"></a>

**Related Modules:**

[DriverUtils](DriverUtils.md)

**Description:**

Declares doubly linked list structures and interfaces. 

This file provides interfaces such as inserting a node from the head or tail of a doubly linked list, checking whether a doubly linked list is empty, traversing a doubly linked list, and merging doubly linked lists.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1603797520093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table594772025093525"></a>
<table><thead align="left"><tr id="row1795130341093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p273314010093525"><a name="p273314010093525"></a><a name="p273314010093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1966313255093525"><a name="p1966313255093525"></a><a name="p1966313255093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row314899233093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719682891093525"><a name="p719682891093525"></a><a name="p719682891093525"></a><a href="DListHead.md">DListHead</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620613612093525"><a name="p620613612093525"></a><a name="p620613612093525"></a>Describes a doubly linked list. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1725118547093525"></a>
<table><thead align="left"><tr id="row409133100093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p742788656093525"><a name="p742788656093525"></a><a name="p742788656093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2004211073093525"><a name="p2004211073093525"></a><a name="p2004211073093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row58794638093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1121001417093525"><a name="p1121001417093525"></a><a name="p1121001417093525"></a><a href="DriverUtils.md#ga818b9cca761fe7bc18e4e417da772976">CONTAINER_OF</a>(ptr, type, member)&nbsp;&nbsp;&nbsp;(type *)((char *)(ptr) - (char *)&amp;((type *)0)-&gt;member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p414044942093525"><a name="p414044942093525"></a><a name="p414044942093525"></a>Obtains the address of a structure variable from its member address. </p>
</td>
</tr>
<tr id="row2135548278093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p771717145093525"><a name="p771717145093525"></a><a name="p771717145093525"></a><a href="DriverUtils.md#ga203de9c01fefc8bbbae746685794cfcc">DLIST_FIRST_ENTRY</a>(ptr, type, member)&nbsp;&nbsp;&nbsp;<a href="DriverUtils.md#ga818b9cca761fe7bc18e4e417da772976">CONTAINER_OF</a>((ptr)-&gt;next, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083637811093525"><a name="p2083637811093525"></a><a name="p2083637811093525"></a>Obtains the first node of a doubly linked list. </p>
</td>
</tr>
<tr id="row651339917093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1682067201093525"><a name="p1682067201093525"></a><a name="p1682067201093525"></a><a href="DriverUtils.md#ga25ac08cc864bd59050f7e2ca77df1f23">DLIST_LAST_ENTRY</a>(ptr, type, member)&nbsp;&nbsp;&nbsp;<a href="DriverUtils.md#ga818b9cca761fe7bc18e4e417da772976">CONTAINER_OF</a>((ptr)-&gt;prev, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264969147093525"><a name="p264969147093525"></a><a name="p264969147093525"></a>Obtains the last node of a doubly linked list. </p>
</td>
</tr>
<tr id="row645071681093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p644103866093525"><a name="p644103866093525"></a><a name="p644103866093525"></a><a href="DriverUtils.md#ga2b53b2bcf35b8cfb32e429cacbcc0a8d">DLIST_FOR_EACH_ENTRY</a>(pos, head, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1766382038093525"><a name="p1766382038093525"></a><a name="p1766382038093525"></a>Traverses all nodes in a doubly linked list. </p>
</td>
</tr>
<tr id="row359502300093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927320317093525"><a name="p927320317093525"></a><a name="p927320317093525"></a><a href="DriverUtils.md#ga8e6f49c1fed85c031f29e8acce377ea0">DLIST_FOR_EACH_ENTRY_SAFE</a>(pos, tmp, head, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1735748325093525"><a name="p1735748325093525"></a><a name="p1735748325093525"></a>Traverses all nodes in a doubly linked list. This function is used to delete the nodes pointed to by <strong id="b639898956093525"><a name="b639898956093525"></a><a name="b639898956093525"></a>pos</strong> during traversal. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1507708443093525"></a>
<table><thead align="left"><tr id="row1574035122093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2079108354093525"><a name="p2079108354093525"></a><a name="p2079108354093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p153035194093525"><a name="p153035194093525"></a><a name="p153035194093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2139944503093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p807267951093525"><a name="p807267951093525"></a><a name="p807267951093525"></a><a href="DriverUtils.md#ga0a86a18ad591f485663834799dd38dea">DListHeadInit</a> (struct <a href="DListHead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579739705093525"><a name="p1579739705093525"></a><a name="p1579739705093525"></a>static void&nbsp;</p>
<p id="p1858585932093525"><a name="p1858585932093525"></a><a name="p1858585932093525"></a>Initializes a doubly linked list. </p>
</td>
</tr>
<tr id="row159452861093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p763163010093525"><a name="p763163010093525"></a><a name="p763163010093525"></a><a href="DriverUtils.md#ga9b4053294ad63f0bdacb4841a14ba208">DListIsEmpty</a> (const struct <a href="DListHead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1072069472093525"><a name="p1072069472093525"></a><a name="p1072069472093525"></a>static bool&nbsp;</p>
<p id="p983248949093525"><a name="p983248949093525"></a><a name="p983248949093525"></a>Checks whether a doubly linked list is empty. </p>
</td>
</tr>
<tr id="row582086299093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p900129574093525"><a name="p900129574093525"></a><a name="p900129574093525"></a><a href="DriverUtils.md#ga42d23fa1f55097bae91664c5e4a78e1e">DListRemove</a> (struct <a href="DListHead.md">DListHead</a> *<a href="entry.md">entry</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141683691093525"><a name="p2141683691093525"></a><a name="p2141683691093525"></a>static void&nbsp;</p>
<p id="p1905526652093525"><a name="p1905526652093525"></a><a name="p1905526652093525"></a>Removes a node from a doubly linked list. </p>
</td>
</tr>
<tr id="row613979785093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p80994046093525"><a name="p80994046093525"></a><a name="p80994046093525"></a><a href="DriverUtils.md#ga60e796c868630dd403ef4fdcc60c12e8">DListInsertHead</a> (struct <a href="DListHead.md">DListHead</a> *<a href="entry.md">entry</a>, struct <a href="DListHead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432833718093525"><a name="p1432833718093525"></a><a name="p1432833718093525"></a>static void&nbsp;</p>
<p id="p1567899504093525"><a name="p1567899504093525"></a><a name="p1567899504093525"></a>Inserts a node from the head of a doubly linked list. </p>
</td>
</tr>
<tr id="row1316007257093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1549634535093525"><a name="p1549634535093525"></a><a name="p1549634535093525"></a><a href="DriverUtils.md#gaa1d386162f8f6401fe8ac6d70d237517">DListInsertTail</a> (struct <a href="DListHead.md">DListHead</a> *<a href="entry.md">entry</a>, struct <a href="DListHead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728671666093525"><a name="p728671666093525"></a><a name="p728671666093525"></a>static void&nbsp;</p>
<p id="p745282989093525"><a name="p745282989093525"></a><a name="p745282989093525"></a>Inserts a node from the tail of a doubly linked list. </p>
</td>
</tr>
<tr id="row38912050093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p352243086093525"><a name="p352243086093525"></a><a name="p352243086093525"></a><a href="DriverUtils.md#gac4acad10a7c49cc4b2d773aedbfa1e11">DListMerge</a> (struct <a href="DListHead.md">DListHead</a> *list, struct <a href="DListHead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2032731145093525"><a name="p2032731145093525"></a><a name="p2032731145093525"></a>static void&nbsp;</p>
<p id="p1529085925093525"><a name="p1529085925093525"></a><a name="p1529085925093525"></a>Merges two linked lists by adding the list specified by <strong id="b841936601093525"><a name="b841936601093525"></a><a name="b841936601093525"></a>list</strong> to the head of the list specified by <strong id="b842556862093525"><a name="b842556862093525"></a><a name="b842556862093525"></a>head</strong> and initializes the merged list. </p>
</td>
</tr>
</tbody>
</table>

