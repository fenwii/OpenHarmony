# strings.h<a name="EN-US_TOPIC_0000001055707984"></a>

## **Overview**<a name="section220905405084832"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Declares commonly used functions for byte sequence operations. 

You can use the functions provided in this file to perform the mathematical operations required during development. Example operations include comparing, copying byte sequences, and setting a byte sequence to 0. You must pay attention to memory management during function calls. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1674401103084832"></a>

## Functions<a name="func-members"></a>

<a name="table318805378084832"></a>
<table><thead align="left"><tr id="row1911916363084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p688273150084832"><a name="p688273150084832"></a><a name="p688273150084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1537088153084832"><a name="p1537088153084832"></a><a name="p1537088153084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row242551690084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1575842201084832"><a name="p1575842201084832"></a><a name="p1575842201084832"></a><a href="utils.md#ga840ecc6fc750bf00e99015d2817b0e12">bcmp</a> (const void *s1, const void *s2, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472603905084832"><a name="p1472603905084832"></a><a name="p1472603905084832"></a>int </p>
<p id="p2102713996084832"><a name="p2102713996084832"></a><a name="p2102713996084832"></a>Compares byte sequences. </p>
</td>
</tr>
<tr id="row1320174572084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1576874659084832"><a name="p1576874659084832"></a><a name="p1576874659084832"></a><a href="utils.md#ga2bf0688adef533a3285e7e0c00f98ff8">bcopy</a> (const void *src, void *dest, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1944465668084832"><a name="p1944465668084832"></a><a name="p1944465668084832"></a>void </p>
<p id="p1516376167084832"><a name="p1516376167084832"></a><a name="p1516376167084832"></a>Copies byte sequences. </p>
</td>
</tr>
<tr id="row980878942084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541770467084832"><a name="p541770467084832"></a><a name="p541770467084832"></a><a href="utils.md#ga59505af7f1c47ff01fdb944801642033">bzero</a> (void *s, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269963347084832"><a name="p269963347084832"></a><a name="p269963347084832"></a>void </p>
<p id="p1348551160084832"><a name="p1348551160084832"></a><a name="p1348551160084832"></a>Sets byte sequences to zero. </p>
</td>
</tr>
<tr id="row710577063084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785575541084832"><a name="p785575541084832"></a><a name="p785575541084832"></a><a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a> (const char *s, int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085695093084832"><a name="p1085695093084832"></a><a name="p1085695093084832"></a>char * </p>
<p id="p1879986203084832"><a name="p1879986203084832"></a><a name="p1879986203084832"></a>Searches for the first position of the matched character in a string. </p>
</td>
</tr>
<tr id="row1031698880084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1627398737084832"><a name="p1627398737084832"></a><a name="p1627398737084832"></a><a href="utils.md#ga83d9aa3251fdee263ad43bf75933de46">rindex</a> (const char *s, int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2028754578084832"><a name="p2028754578084832"></a><a name="p2028754578084832"></a>char * </p>
<p id="p630366338084832"><a name="p630366338084832"></a><a name="p630366338084832"></a>Searches for the last position of the matched character in a string. </p>
</td>
</tr>
<tr id="row358127209084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p527746642084832"><a name="p527746642084832"></a><a name="p527746642084832"></a><a href="utils.md#ga2385d975eddea296daa497e5d36febc9">ffs</a> (int i)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805049524084832"><a name="p805049524084832"></a><a name="p805049524084832"></a>int </p>
<p id="p570223672084832"><a name="p570223672084832"></a><a name="p570223672084832"></a>Searches for the first bit in a word of the integer type. </p>
</td>
</tr>
<tr id="row506115753084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p364251180084832"><a name="p364251180084832"></a><a name="p364251180084832"></a><a href="utils.md#ga73690a58537a6dbafa9aa4b3afa7baac">ffsl</a> (long int i)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082233150084832"><a name="p2082233150084832"></a><a name="p2082233150084832"></a>int </p>
<p id="p162231411084832"><a name="p162231411084832"></a><a name="p162231411084832"></a>Searches for the first bit in a word of the long integer type. </p>
</td>
</tr>
<tr id="row838537570084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p771211862084832"><a name="p771211862084832"></a><a name="p771211862084832"></a><a href="utils.md#gae7eaa572ad4e097865bd409b121fb33c">ffsll</a> (long long int i)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854233074084832"><a name="p854233074084832"></a><a name="p854233074084832"></a>int </p>
<p id="p890822020084832"><a name="p890822020084832"></a><a name="p890822020084832"></a>Searches for the first bit in a word of the 8-byte long integer type. </p>
</td>
</tr>
<tr id="row249693188084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p138021983084832"><a name="p138021983084832"></a><a name="p138021983084832"></a><a href="utils.md#ga2436604f43de7f27e7434ceea7d64528">strcasecmp</a> (const char *_l, const char *_r)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1401515019084832"><a name="p1401515019084832"></a><a name="p1401515019084832"></a>int </p>
<p id="p588872970084832"><a name="p588872970084832"></a><a name="p588872970084832"></a>Compares two strings (string 1 and string 2), regardless of the letter case. </p>
</td>
</tr>
<tr id="row85985761084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1796172292084832"><a name="p1796172292084832"></a><a name="p1796172292084832"></a><a href="utils.md#ga103fd689d8438a246e0cd4d90cb084ac">strncasecmp</a> (const char *_l, const char *_r, size_t n)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p271578815084832"><a name="p271578815084832"></a><a name="p271578815084832"></a>int </p>
<p id="p909487293084832"><a name="p909487293084832"></a><a name="p909487293084832"></a>Compares a specified length of two strings (string 1 and string 2), regardless of the letter case. </p>
</td>
</tr>
</tbody>
</table>

