# search.h<a name="ZH-CN_TOPIC_0000001055108027"></a>

## **Overview**<a name="section2095865854084832"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Provides functions and related data structures, such as creating, destroying, or searching for a hash table. 

You can use the functions provided in this file to perform operations related to wide character types during development, such as, creating, destroying, or searching for a hash table, and creating or searching for a binary tree. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1898132714084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1428904415084832"></a>
<table><thead align="left"><tr id="row1055834200084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1941498265084832"><a name="p1941498265084832"></a><a name="p1941498265084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1823914872084832"><a name="p1823914872084832"></a><a name="p1823914872084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row935675605084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91649125084832"><a name="p91649125084832"></a><a name="p91649125084832"></a><a href="entry.md">entry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436672527084832"><a name="p436672527084832"></a><a name="p436672527084832"></a>Defines a hash table entry. </p>
</td>
</tr>
<tr id="row2008590779084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561627315084832"><a name="p1561627315084832"></a><a name="p1561627315084832"></a><a href="qelem.md">qelem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740165505084832"><a name="p740165505084832"></a><a name="p740165505084832"></a>Creates a queue from the doubly linked list for <a href="UTILS.md#ga7dc680d5d6d07984f96737c220058d64">insque</a> and <a href="UTILS.md#ga1d2e353620a8dc3bb2702831607a3fc1">remque</a>. </p>
</td>
</tr>
<tr id="row813672276084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226533583084832"><a name="p226533583084832"></a><a name="p226533583084832"></a><a href="hsearch_data.md">hsearch_data</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389304576084832"><a name="p1389304576084832"></a><a name="p1389304576084832"></a>Defines a hash table. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1217134320084832"></a>
<table><thead align="left"><tr id="row1143777142084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1387772072084832"><a name="p1387772072084832"></a><a name="p1387772072084832"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1406886958084832"><a name="p1406886958084832"></a><a name="p1406886958084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row767617264084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p786414861084832"><a name="p786414861084832"></a><a name="p786414861084832"></a><a href="UTILS.md#gaf609835b21489409e39a22ed20313ab8">ENTRY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561047772084832"><a name="p1561047772084832"></a><a name="p1561047772084832"></a> typedef struct <a href="entry.md">entry</a>&nbsp;</p>
<p id="p248696984084832"><a name="p248696984084832"></a><a name="p248696984084832"></a>Defines a hash table entry. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table628571984084832"></a>
<table><thead align="left"><tr id="row1605386500084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p323910773084832"><a name="p323910773084832"></a><a name="p323910773084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1275293549084832"><a name="p1275293549084832"></a><a name="p1275293549084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1594042147084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1422137759084832"><a name="p1422137759084832"></a><a name="p1422137759084832"></a><a href="UTILS.md#gafb18cb23be808765135c3aa903df62fd">hcreate</a> (size_t nel)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p541422531084832"><a name="p541422531084832"></a><a name="p541422531084832"></a>int&nbsp;</p>
<p id="p323287233084832"><a name="p323287233084832"></a><a name="p323287233084832"></a>Creates a hash table based on the number of entries. </p>
</td>
</tr>
<tr id="row471757059084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1269370464084832"><a name="p1269370464084832"></a><a name="p1269370464084832"></a><a href="UTILS.md#ga883c8dedada64c9525c78bfa56ad69bf">hdestroy</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216591345084832"><a name="p216591345084832"></a><a name="p216591345084832"></a>void&nbsp;</p>
<p id="p1058192982084832"><a name="p1058192982084832"></a><a name="p1058192982084832"></a>Destroys a hash table. </p>
</td>
</tr>
<tr id="row1689805187084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p986878280084832"><a name="p986878280084832"></a><a name="p986878280084832"></a><a href="UTILS.md#ga8082cd062e20579f6a981bb73963b3f4">hsearch</a> (<a href="UTILS.md#gaf609835b21489409e39a22ed20313ab8">ENTRY</a> item, ACTION action)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238117922084832"><a name="p1238117922084832"></a><a name="p1238117922084832"></a><a href="UTILS.md#gaf609835b21489409e39a22ed20313ab8">ENTRY</a> *&nbsp;</p>
<p id="p966646938084832"><a name="p966646938084832"></a><a name="p966646938084832"></a>Adds or searches for a hash entry. </p>
</td>
</tr>
<tr id="row1373086841084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1439652699084832"><a name="p1439652699084832"></a><a name="p1439652699084832"></a><a href="UTILS.md#ga038ec523340da68e90a5f22e1e4e5520">hcreate_r</a> (size_t nel, struct <a href="hsearch_data.md">hsearch_data</a> *htab)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1527714999084832"><a name="p1527714999084832"></a><a name="p1527714999084832"></a>int&nbsp;</p>
<p id="p92898088084832"><a name="p92898088084832"></a><a name="p92898088084832"></a>Creates a hash table based on the number of entries and its description. </p>
</td>
</tr>
<tr id="row1952263373084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p391353750084832"><a name="p391353750084832"></a><a name="p391353750084832"></a><a href="UTILS.md#gafb5169db08a09e98495c26bdd7e6d8dc">hdestroy_r</a> (struct <a href="hsearch_data.md">hsearch_data</a> *htab)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090871344084832"><a name="p2090871344084832"></a><a name="p2090871344084832"></a>void&nbsp;</p>
<p id="p871760369084832"><a name="p871760369084832"></a><a name="p871760369084832"></a>Destroys a hash table. </p>
</td>
</tr>
<tr id="row1817289055084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p27409443084832"><a name="p27409443084832"></a><a name="p27409443084832"></a><a href="UTILS.md#ga22072d94699358ab02286f4c7b6aac55">hsearch_r</a> (<a href="UTILS.md#gaf609835b21489409e39a22ed20313ab8">ENTRY</a> item, ACTION action, <a href="UTILS.md#gaf609835b21489409e39a22ed20313ab8">ENTRY</a> **retval, struct <a href="hsearch_data.md">hsearch_data</a> *htab)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p933186558084832"><a name="p933186558084832"></a><a name="p933186558084832"></a>int&nbsp;</p>
<p id="p1562829332084832"><a name="p1562829332084832"></a><a name="p1562829332084832"></a>Searches for a hash table. </p>
</td>
</tr>
<tr id="row1120202478084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p77918855084832"><a name="p77918855084832"></a><a name="p77918855084832"></a><a href="UTILS.md#ga7dc680d5d6d07984f96737c220058d64">insque</a> (void *element, void *pred)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p201509557084832"><a name="p201509557084832"></a><a name="p201509557084832"></a>void&nbsp;</p>
<p id="p1955400905084832"><a name="p1955400905084832"></a><a name="p1955400905084832"></a>Adds an entry to a queue. </p>
</td>
</tr>
<tr id="row1498806581084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1411728870084832"><a name="p1411728870084832"></a><a name="p1411728870084832"></a><a href="UTILS.md#ga1d2e353620a8dc3bb2702831607a3fc1">remque</a> (void *elem)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p843122873084832"><a name="p843122873084832"></a><a name="p843122873084832"></a>void&nbsp;</p>
<p id="p1485454687084832"><a name="p1485454687084832"></a><a name="p1485454687084832"></a>Removes an entry from a queue. </p>
</td>
</tr>
<tr id="row1106721771084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1321326596084832"><a name="p1321326596084832"></a><a name="p1321326596084832"></a><a href="UTILS.md#ga2e48c29ae7f3ef8f5707f4cc4f4ef608">lsearch</a> (const void *key, const void *base, size_t *nelp, size_t width, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1636656383084832"><a name="p1636656383084832"></a><a name="p1636656383084832"></a>void *&nbsp;</p>
<p id="p1489206967084832"><a name="p1489206967084832"></a><a name="p1489206967084832"></a>Performs a linear search for a key in the array and adds a key to the end of the array if the key is not found. </p>
</td>
</tr>
<tr id="row2043033534084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p225621448084832"><a name="p225621448084832"></a><a name="p225621448084832"></a><a href="UTILS.md#ga9f8c694512c6c8a53f7e5a5f5e25cf86">lfind</a> (const void *key, const void *base, size_t *nelp, size_t width, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1975423887084832"><a name="p1975423887084832"></a><a name="p1975423887084832"></a>void *&nbsp;</p>
<p id="p115084262084832"><a name="p115084262084832"></a><a name="p115084262084832"></a>Performs a linear search for a key in the array. </p>
</td>
</tr>
<tr id="row132347029084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1788773448084832"><a name="p1788773448084832"></a><a name="p1788773448084832"></a><a href="UTILS.md#ga58961b9d8ec6333735b53fd0999eff17">tdelete</a> (const void *key, void **rootp, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901767552084832"><a name="p1901767552084832"></a><a name="p1901767552084832"></a>void *&nbsp;</p>
<p id="p402149013084832"><a name="p402149013084832"></a><a name="p402149013084832"></a>Deletes a key from the binary tree. </p>
</td>
</tr>
<tr id="row1472891968084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1649708395084832"><a name="p1649708395084832"></a><a name="p1649708395084832"></a><a href="UTILS.md#ga576dc73ee732b840e09c88972b7d487e">tfind</a> (const void *key, void *const *rootp, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756924118084832"><a name="p756924118084832"></a><a name="p756924118084832"></a>void *&nbsp;</p>
<p id="p549918536084832"><a name="p549918536084832"></a><a name="p549918536084832"></a>Searches for a key in the binary tree. </p>
</td>
</tr>
<tr id="row1585207759084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429180707084832"><a name="p429180707084832"></a><a name="p429180707084832"></a><a href="UTILS.md#ga197c455a4e5f17cb8565be72d18344cc">tsearch</a> (const void *key, void *const *rootp, int(*compar)(const void *, const void *))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2022709116084832"><a name="p2022709116084832"></a><a name="p2022709116084832"></a>void *&nbsp;</p>
<p id="p1293139361084832"><a name="p1293139361084832"></a><a name="p1293139361084832"></a>Searches for a key in the binary tree and adds a key to the tree if the key is not found. </p>
</td>
</tr>
<tr id="row730118548084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858448897084832"><a name="p858448897084832"></a><a name="p858448897084832"></a><a href="UTILS.md#ga4d8ee780402dd74ec06e7b5089565168">twalk</a> (const void *root, void(*action)(const void *nodep, VISIT which, int depth))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1553219314084832"><a name="p1553219314084832"></a><a name="p1553219314084832"></a>void&nbsp;</p>
<p id="p1379259659084832"><a name="p1379259659084832"></a><a name="p1379259659084832"></a>Traverses a binary tree from left to right. </p>
</td>
</tr>
<tr id="row628429883084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21453645084832"><a name="p21453645084832"></a><a name="p21453645084832"></a><a href="UTILS.md#gab12d1869fd9d20ce6706fcef217ba222">tdestroy</a> (void *root, void(*free_node)(void *nodep))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p821252188084832"><a name="p821252188084832"></a><a name="p821252188084832"></a>void&nbsp;</p>
<p id="p711429991084832"><a name="p711429991084832"></a><a name="p711429991084832"></a>Releases all nodes in the binary tree. </p>
</td>
</tr>
</tbody>
</table>

