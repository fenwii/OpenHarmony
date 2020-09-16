# wordexp\_t<a name="ZH-CN_TOPIC_0000001054598211"></a>

## **Overview**<a name="section552510509084843"></a>

**Related Modules:**

[IO](IO.md)

**Description:**

Describes information about word expansion. 

## **Summary**<a name="section1291725668084843"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table449572061084843"></a>
<table><thead align="left"><tr id="row1577540401084843"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p869955480084843"><a name="p869955480084843"></a><a name="p869955480084843"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p741234666084843"><a name="p741234666084843"></a><a name="p741234666084843"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2014877982084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p787330537084843"><a name="p787330537084843"></a><a name="p787330537084843"></a><a href="wordexp_t.md#aeca511502c524dbf33993c02cf7127c7">we_wordc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1346326072084843"><a name="p1346326072084843"></a><a name="p1346326072084843"></a>size_t&nbsp;</p>
</td>
</tr>
<tr id="row158358983084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1205112473084843"><a name="p1205112473084843"></a><a name="p1205112473084843"></a><a href="wordexp_t.md#a00d1aa490abf8b5d0f6a1e04a323329b">we_wordv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67259654084843"><a name="p67259654084843"></a><a name="p67259654084843"></a>char **&nbsp;</p>
</td>
</tr>
<tr id="row544074418084843"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1552131989084843"><a name="p1552131989084843"></a><a name="p1552131989084843"></a><a href="wordexp_t.md#a956cc2725b2ed52f61efd3fc8dfca853">we_offs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p241339546084843"><a name="p241339546084843"></a><a name="p241339546084843"></a>size_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section2067873355084843"></a>

## **Field Documentation**<a name="section1092167936084843"></a>

## we\_offs<a name="a956cc2725b2ed52f61efd3fc8dfca853"></a>

```
size_t wordexp_t::we_offs
```

 **Description:**

Offset of the word string 

## we\_wordc<a name="aeca511502c524dbf33993c02cf7127c7"></a>

```
size_t wordexp_t::we_wordc
```

 **Description:**

Number of words 

## we\_wordv<a name="a00d1aa490abf8b5d0f6a1e04a323329b"></a>

```
char** wordexp_t::we_wordv
```

 **Description:**

Address of the word string 

