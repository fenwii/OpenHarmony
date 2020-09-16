# err.h<a name="EN-US_TOPIC_0000001055547976"></a>

## **Overview**<a name="section869829171084829"></a>

**Related Modules:**

[IO](io.md)

**Description:**

Provides common functions for error messages. 

You can use the functions provided in this file to implement error output operations required during development. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1129957190084829"></a>

## Functions<a name="func-members"></a>

<a name="table1685461947084829"></a>
<table><thead align="left"><tr id="row1490505295084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2095495925084829"><a name="p2095495925084829"></a><a name="p2095495925084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1749883894084829"><a name="p1749883894084829"></a><a name="p1749883894084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2135262305084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2009257411084829"><a name="p2009257411084829"></a><a name="p2009257411084829"></a><a href="io.md#gaf80d19f1297a11626fab61a248959c71">warn</a> (const char *fmt,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757558440084829"><a name="p757558440084829"></a><a name="p757558440084829"></a>void </p>
<p id="p1977726969084829"><a name="p1977726969084829"></a><a name="p1977726969084829"></a>Displays a formatted error message on the standard error (stderr) output. </p>
</td>
</tr>
<tr id="row1181900670084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382369501084829"><a name="p382369501084829"></a><a name="p382369501084829"></a><a href="io.md#ga9ca1ffba0c6f5df7b172d25917611b4a">vwarn</a> (const char *fmt, va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p255867660084829"><a name="p255867660084829"></a><a name="p255867660084829"></a>void </p>
<p id="p594314931084829"><a name="p594314931084829"></a><a name="p594314931084829"></a>Displays a formatted error message on the stderr output. </p>
</td>
</tr>
<tr id="row1371109976084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1483790992084829"><a name="p1483790992084829"></a><a name="p1483790992084829"></a><a href="io.md#ga58f3d9691c146f86e562022d39567b7f">warnx</a> (const char *fmt,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072949724084829"><a name="p2072949724084829"></a><a name="p2072949724084829"></a>void </p>
<p id="p215802802084829"><a name="p215802802084829"></a><a name="p215802802084829"></a>Displays a formatted error message on the stderr output. </p>
</td>
</tr>
<tr id="row1184007372084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085833190084829"><a name="p2085833190084829"></a><a name="p2085833190084829"></a><a href="io.md#ga22924aaaaa6b6e8bba4c76d0a0fe86cd">vwarnx</a> (const char *fmt, va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1929972019084829"><a name="p1929972019084829"></a><a name="p1929972019084829"></a>void </p>
<p id="p1471276701084829"><a name="p1471276701084829"></a><a name="p1471276701084829"></a>Displays a formatted error message on the stderr output. </p>
</td>
</tr>
<tr id="row1348810693084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2101151882084829"><a name="p2101151882084829"></a><a name="p2101151882084829"></a><a href="io.md#gaa6b66a9a8eb4be40e4424a4dc92ae056">err</a> (int eval, const char *fmt, va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1975004817084829"><a name="p1975004817084829"></a><a name="p1975004817084829"></a>void </p>
<p id="p864726446084829"><a name="p864726446084829"></a><a name="p864726446084829"></a>Displays error information. </p>
</td>
</tr>
<tr id="row59290744084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1593002935084829"><a name="p1593002935084829"></a><a name="p1593002935084829"></a><a href="io.md#gaeaca83913c785b95d6c50f35207ff739">errx</a> (int eval, const char *fmt,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278298497084829"><a name="p278298497084829"></a><a name="p278298497084829"></a>void </p>
<p id="p1075001882084829"><a name="p1075001882084829"></a><a name="p1075001882084829"></a>Displays error information. </p>
</td>
</tr>
<tr id="row1595209599084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p588805884084829"><a name="p588805884084829"></a><a name="p588805884084829"></a><a href="io.md#gaf5491fca8b356da75d96fc469bf32ea6">verr</a> (int eval, const char *fmt, va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p61117255084829"><a name="p61117255084829"></a><a name="p61117255084829"></a>void </p>
<p id="p782942606084829"><a name="p782942606084829"></a><a name="p782942606084829"></a>Displays error information. </p>
</td>
</tr>
<tr id="row999028761084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p966163332084829"><a name="p966163332084829"></a><a name="p966163332084829"></a><a href="io.md#ga4b5f9ccd84c00dc473329e4bf64125e1">verrx</a> (int eval, const char *fmt, va_list args)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p716010430084829"><a name="p716010430084829"></a><a name="p716010430084829"></a>void </p>
<p id="p1554277137084829"><a name="p1554277137084829"></a><a name="p1554277137084829"></a>Displays a formatted error message. </p>
</td>
</tr>
</tbody>
</table>

