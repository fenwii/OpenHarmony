# iconv.h<a name="EN-US_TOPIC_0000001055547978"></a>

## **Overview**<a name="section2080269519084830"></a>

**Related Modules:**

[IO](io.md)

**Description:**

Declares functions related to the I/O character set conversion. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section972639167084830"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table2037174226084830"></a>
<table><thead align="left"><tr id="row1589756495084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1513707284084830"><a name="p1513707284084830"></a><a name="p1513707284084830"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1758964260084830"><a name="p1758964260084830"></a><a name="p1758964260084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row861538130084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680517810084830"><a name="p680517810084830"></a><a name="p680517810084830"></a><a href="io.md#ga72517f6ffadddaafa9d51dee9b535c9f">iconv_t</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197765638084830"><a name="p1197765638084830"></a><a name="p1197765638084830"></a> typedef void * </p>
<p id="p997763674084830"><a name="p997763674084830"></a><a name="p997763674084830"></a>Type of the character set conversion descriptor. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1696880125084830"></a>
<table><thead align="left"><tr id="row1722070593084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1715130880084830"><a name="p1715130880084830"></a><a name="p1715130880084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p271290989084830"><a name="p271290989084830"></a><a name="p271290989084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1310852221084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p764216310084830"><a name="p764216310084830"></a><a name="p764216310084830"></a><a href="io.md#ga934548ab8aaae237ac5cce0ed0b3edec">iconv_open</a> (const char *to, const char *from)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1343009333084830"><a name="p1343009333084830"></a><a name="p1343009333084830"></a><a href="io.md#ga72517f6ffadddaafa9d51dee9b535c9f">iconv_t</a> </p>
<p id="p1774028513084830"><a name="p1774028513084830"></a><a name="p1774028513084830"></a>Obtain a character set conversion descriptor. </p>
</td>
</tr>
<tr id="row258328759084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2128215912084830"><a name="p2128215912084830"></a><a name="p2128215912084830"></a><a href="io.md#gab7c1300a663def659ce6d4a01076c39d">iconv</a> (<a href="io.md#ga72517f6ffadddaafa9d51dee9b535c9f">iconv_t</a> cd, char **restrict in, size_t *restrict inb, char **restrict out, size_t *restrict outb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1735504893084830"><a name="p1735504893084830"></a><a name="p1735504893084830"></a>size_t </p>
<p id="p326594027084830"><a name="p326594027084830"></a><a name="p326594027084830"></a>Converts a character set. </p>
</td>
</tr>
<tr id="row619317271084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1206469449084830"><a name="p1206469449084830"></a><a name="p1206469449084830"></a><a href="io.md#ga062da5f802d9e274a8702f11921e691b">iconv_close</a> (<a href="io.md#ga72517f6ffadddaafa9d51dee9b535c9f">iconv_t</a> cd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1606477763084830"><a name="p1606477763084830"></a><a name="p1606477763084830"></a>int </p>
<p id="p236298488084830"><a name="p236298488084830"></a><a name="p236298488084830"></a>Closes a character set conversion descriptor. </p>
</td>
</tr>
</tbody>
</table>

