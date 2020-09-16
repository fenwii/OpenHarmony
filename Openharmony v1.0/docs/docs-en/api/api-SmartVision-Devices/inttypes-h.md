# inttypes.h<a name="EN-US_TOPIC_0000001055228016"></a>

## **Overview**<a name="section1152430964084830"></a>

**Related Modules:**

[UTILS](utils.md)

**Description:**

Provides functions and related data structures for conversion between character strings and plural. 

You can use the functions provided in this file to perform operations related to wide character types during development, for example, performing a division operation, converting a character string to an imax-type parameter, or converting a character string to an umax-type parameter. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section560622519084830"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table309973849084830"></a>
<table><thead align="left"><tr id="row1947611322084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1058902836084830"><a name="p1058902836084830"></a><a name="p1058902836084830"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1793912123084830"><a name="p1793912123084830"></a><a name="p1793912123084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1329353504084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559365537084830"><a name="p559365537084830"></a><a name="p559365537084830"></a><a href="imaxdiv_t.md">imaxdiv_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1476111999084830"><a name="p1476111999084830"></a><a name="p1476111999084830"></a>Stores the division result. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table362782923084830"></a>
<table><thead align="left"><tr id="row1106153162084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2045994281084830"><a name="p2045994281084830"></a><a name="p2045994281084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p193894080084830"><a name="p193894080084830"></a><a name="p193894080084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row920780165084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p332343110084830"><a name="p332343110084830"></a><a name="p332343110084830"></a><a href="utils.md#gad9e8a565a34b6981f500d88773ec7bcd">imaxabs</a> (intmax_t j)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383721129084830"><a name="p1383721129084830"></a><a name="p1383721129084830"></a>intmax_t </p>
<p id="p77311208084830"><a name="p77311208084830"></a><a name="p77311208084830"></a>Calculates the absolute value of an input parameter of the integer type. </p>
</td>
</tr>
<tr id="row1579357056084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p503847671084830"><a name="p503847671084830"></a><a name="p503847671084830"></a><a href="utils.md#ga17335f74f0abcfd3047de48f6823f527">imaxdiv</a> (intmax_t numerator, intmax_t denominator)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p543712150084830"><a name="p543712150084830"></a><a name="p543712150084830"></a><a href="imaxdiv_t.md">imaxdiv_t</a> </p>
<p id="p1130268431084830"><a name="p1130268431084830"></a><a name="p1130268431084830"></a>Calculates the quotient and remainder after the division operation is performed on an integer. </p>
</td>
</tr>
<tr id="row156682433084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1468337006084830"><a name="p1468337006084830"></a><a name="p1468337006084830"></a><a href="utils.md#ga996146b4c9a860837a1f09868a6c0a61">strtoimax</a> (const char *str, char **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p628248382084830"><a name="p628248382084830"></a><a name="p628248382084830"></a>intmax_t </p>
<p id="p1166917022084830"><a name="p1166917022084830"></a><a name="p1166917022084830"></a>Parses a string to a value of the <strong id="b826026764084830"><a name="b826026764084830"></a><a name="b826026764084830"></a>intmax_t</strong> type. </p>
</td>
</tr>
<tr id="row1677155703084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1303619552084830"><a name="p1303619552084830"></a><a name="p1303619552084830"></a><a href="utils.md#ga706f89e2b5a9a623207f2d77b19ff6f8">strtoumax</a> (const char *str, char **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p111238268084830"><a name="p111238268084830"></a><a name="p111238268084830"></a>uintmax_t </p>
<p id="p1663834779084830"><a name="p1663834779084830"></a><a name="p1663834779084830"></a>Parses a string to a value of the <strong id="b951296161084830"><a name="b951296161084830"></a><a name="b951296161084830"></a>uintmax_t</strong> type. </p>
</td>
</tr>
<tr id="row729777244084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2098906887084830"><a name="p2098906887084830"></a><a name="p2098906887084830"></a><a href="utils.md#gaab72fde556caed7f725c0bece02e4cc9">wcstoimax</a> (const wchar_t *str, wchar_t **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492427295084830"><a name="p1492427295084830"></a><a name="p1492427295084830"></a>intmax_t </p>
<p id="p1212877834084830"><a name="p1212877834084830"></a><a name="p1212877834084830"></a>Parses a string to a value of the <strong id="b1559742586084830"><a name="b1559742586084830"></a><a name="b1559742586084830"></a>intmax_t</strong> type. </p>
</td>
</tr>
<tr id="row2099358761084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p384041740084830"><a name="p384041740084830"></a><a name="p384041740084830"></a><a href="utils.md#gaaf3fa62320e289517f453bf1e470a1f9">wcstoumax</a> (const wchar_t *str, wchar_t **endptr, int base)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939056205084830"><a name="p1939056205084830"></a><a name="p1939056205084830"></a>uintmax_t </p>
<p id="p725376182084830"><a name="p725376182084830"></a><a name="p725376182084830"></a>Parses a string to a value of the <strong id="b1283440092084830"><a name="b1283440092084830"></a><a name="b1283440092084830"></a>uintmax_t</strong> type. </p>
</td>
</tr>
</tbody>
</table>

