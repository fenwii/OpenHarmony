# nl\_types.h<a name="ZH-CN_TOPIC_0000001055189447"></a>

## **Overview**<a name="section1347519793084831"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Defines I/O multiplexing functions related to message catalog operations. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section293918511084831"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table1502828043084831"></a>
<table><thead align="left"><tr id="row538762449084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p425608885084831"><a name="p425608885084831"></a><a name="p425608885084831"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1727295747084831"><a name="p1727295747084831"></a><a name="p1727295747084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row772764961084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101824178084831"><a name="p1101824178084831"></a><a name="p1101824178084831"></a><a href="IO.md#ga3f305b6699c89f91aecfc0b5f8604a5f">nl_catd</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175616442084831"><a name="p1175616442084831"></a><a name="p1175616442084831"></a> typedef void *&nbsp;</p>
<p id="p228499546084831"><a name="p228499546084831"></a><a name="p228499546084831"></a>Type of message catalog descriptor. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1282574167084831"></a>
<table><thead align="left"><tr id="row1099185115084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p93449449084831"><a name="p93449449084831"></a><a name="p93449449084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p950769041084831"><a name="p950769041084831"></a><a name="p950769041084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row133605840084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1867015825084831"><a name="p1867015825084831"></a><a name="p1867015825084831"></a><a href="IO.md#gac898c5cfd3f2352d639b8356ff6aa343">catopen</a> (const char *name, int oflag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1924227789084831"><a name="p1924227789084831"></a><a name="p1924227789084831"></a><a href="IO.md#ga3f305b6699c89f91aecfc0b5f8604a5f">nl_catd</a>&nbsp;</p>
<p id="p1696727968084831"><a name="p1696727968084831"></a><a name="p1696727968084831"></a>Opens a message catalog and returns its descriptor. </p>
</td>
</tr>
<tr id="row373491066084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451106929084831"><a name="p451106929084831"></a><a name="p451106929084831"></a><a href="IO.md#gaa615f433a6a187d0ee5ed647efc0e091">catgets</a> (<a href="IO.md#ga3f305b6699c89f91aecfc0b5f8604a5f">nl_catd</a> catd, int set_id, int msg_id, const char *s)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p810738072084831"><a name="p810738072084831"></a><a name="p810738072084831"></a>char *&nbsp;</p>
<p id="p20515322084831"><a name="p20515322084831"></a><a name="p20515322084831"></a>Obtains information from a message catalog. </p>
</td>
</tr>
<tr id="row1363252747084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1198466531084831"><a name="p1198466531084831"></a><a name="p1198466531084831"></a><a href="IO.md#ga87f06c3df6f24c6b46a9c7fe13e2cb9c">catclose</a> (<a href="IO.md#ga3f305b6699c89f91aecfc0b5f8604a5f">nl_catd</a> catd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1860785829084831"><a name="p1860785829084831"></a><a name="p1860785829084831"></a>int&nbsp;</p>
<p id="p1678856326084831"><a name="p1678856326084831"></a><a name="p1678856326084831"></a>Closes a catalog descriptor. </p>
</td>
</tr>
</tbody>
</table>

