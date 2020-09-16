# locale.h<a name="ZH-CN_TOPIC_0000001055387984"></a>

## **Overview**<a name="section210185372084830"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Provides functions to set and obtain the locale language environment. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1379331042084830"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table799676401084830"></a>
<table><thead align="left"><tr id="row1960199730084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p330248587084830"><a name="p330248587084830"></a><a name="p330248587084830"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p89075725084830"><a name="p89075725084830"></a><a name="p89075725084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row551165383084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14785288084830"><a name="p14785288084830"></a><a name="p14785288084830"></a><a href="lconv.md">lconv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1896088568084830"><a name="p1896088568084830"></a><a name="p1896088568084830"></a>Indicates format information about a number. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1830795738084830"></a>
<table><thead align="left"><tr id="row385686958084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1326197745084830"><a name="p1326197745084830"></a><a name="p1326197745084830"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p307367134084830"><a name="p307367134084830"></a><a name="p307367134084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row835930896084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1895761004084830"><a name="p1895761004084830"></a><a name="p1895761004084830"></a><a href="IO.md#ga07c66689961056725d7f50231d740ba9">LC_CTYPE</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p855223400084830"><a name="p855223400084830"></a><a name="p855223400084830"></a>Language symbol type, which affects character classification and case conversion. </p>
</td>
</tr>
<tr id="row1025053422084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390121169084830"><a name="p390121169084830"></a><a name="p390121169084830"></a><a href="IO.md#ga158abb82c565096465ade138c98970d0">LC_NUMERIC</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1213061376084830"><a name="p1213061376084830"></a><a name="p1213061376084830"></a>Number type, which affects the number format. </p>
</td>
</tr>
<tr id="row1591987602084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p288779010084830"><a name="p288779010084830"></a><a name="p288779010084830"></a><a href="IO.md#gaa652c62b53b6bf728d592bfbdc7d5852">LC_TIME</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296898898084830"><a name="p1296898898084830"></a><a name="p1296898898084830"></a>Time type, which affects date and time formats. </p>
</td>
</tr>
<tr id="row1157029147084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079968047084830"><a name="p2079968047084830"></a><a name="p2079968047084830"></a><a href="IO.md#gaab9cf7b1a206fb75e5884934c8d676db">LC_COLLATE</a>&nbsp;&nbsp;&nbsp;3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1689909101084830"><a name="p1689909101084830"></a><a name="p1689909101084830"></a>Character sorting type, which affects string comparison and sorting habits. </p>
</td>
</tr>
<tr id="row810630514084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003724437084830"><a name="p2003724437084830"></a><a name="p2003724437084830"></a><a href="IO.md#ga6d033a83772ef6e6c10dbf13a6a58fb7">LC_MONETARY</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1869679010084830"><a name="p1869679010084830"></a><a name="p1869679010084830"></a>Monetary type, which affects monetary information. </p>
</td>
</tr>
<tr id="row357504560084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985622431084830"><a name="p1985622431084830"></a><a name="p1985622431084830"></a><a href="IO.md#ga7195d6f0a8d1b9d164a3988a1b8249e8">LC_MESSAGES</a>&nbsp;&nbsp;&nbsp;5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665331074084830"><a name="p1665331074084830"></a><a name="p1665331074084830"></a>Message type, which affects prompt information, error information, status information, titles, labels, buttons, and menus. </p>
</td>
</tr>
<tr id="row985639341084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637948569084830"><a name="p637948569084830"></a><a name="p637948569084830"></a><a href="IO.md#ga9cc5213b5dca4f8e48e64586ee444c33">LC_ALL</a>&nbsp;&nbsp;&nbsp;6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p903964444084830"><a name="p903964444084830"></a><a name="p903964444084830"></a>All types, which affect all content of locale settings. If <strong id="b1021537122084830"><a name="b1021537122084830"></a><a name="b1021537122084830"></a>LC_ALL</strong> is set, the locale information of all types is set to be consistent with <strong id="b565099051084830"><a name="b565099051084830"></a><a name="b565099051084830"></a>LC_ALL</strong>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table273463549084830"></a>
<table><thead align="left"><tr id="row104807650084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p255246178084830"><a name="p255246178084830"></a><a name="p255246178084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1832690548084830"><a name="p1832690548084830"></a><a name="p1832690548084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row388853042084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p371249010084830"><a name="p371249010084830"></a><a name="p371249010084830"></a><a href="IO.md#gafe784c4f5d12b74272740c5211c960c5">setlocale</a> (int category, const char *locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p451876863084830"><a name="p451876863084830"></a><a name="p451876863084830"></a>char *&nbsp;</p>
<p id="p130708480084830"><a name="p130708480084830"></a><a name="p130708480084830"></a>Sets the current locale information based on input parameters. </p>
</td>
</tr>
<tr id="row1126225704084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2046744019084830"><a name="p2046744019084830"></a><a name="p2046744019084830"></a><a href="IO.md#ga69b40f71a20a7c8bd67b9eeeae7f40c9">localeconv</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352404636084830"><a name="p352404636084830"></a><a name="p352404636084830"></a>struct <a href="lconv.md">lconv</a> *&nbsp;</p>
<p id="p1696918670084830"><a name="p1696918670084830"></a><a name="p1696918670084830"></a>Obtains the locale information about a region and stores them in <a href="lconv.md">lconv</a>. </p>
</td>
</tr>
</tbody>
</table>

