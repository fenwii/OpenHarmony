# ProgramInfo<a name="EN-US_TOPIC_0000001055518124"></a>

## **Overview**<a name="section1465149156093536"></a>

**Related Modules:**

[Format](format.md)

**Description:**

Defines program information. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1833560366093536"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2026415345093536"></a>
<table><thead align="left"><tr id="row1531560732093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p694469234093536"><a name="p694469234093536"></a><a name="p694469234093536"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p125164392093536"><a name="p125164392093536"></a><a name="p125164392093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1055605828093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886638847093536"><a name="p1886638847093536"></a><a name="p1886638847093536"></a><a href="programinfo.md#a37665885745484c665fd7c3f7c4e0257">programId</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135967169093536"><a name="p135967169093536"></a><a name="p135967169093536"></a>int32_t </p>
</td>
</tr>
<tr id="row18950369093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p964908065093536"><a name="p964908065093536"></a><a name="p964908065093536"></a><a href="programinfo.md#a652dc8e396a6c8337f24ef19a60ff8d5">durationMs</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597132769093536"><a name="p1597132769093536"></a><a name="p1597132769093536"></a>int64_t </p>
</td>
</tr>
<tr id="row626236416093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p225781734093536"><a name="p225781734093536"></a><a name="p225781734093536"></a><a href="programinfo.md#a63ffbb3059e57c139cb3801c8188c662">trackNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303690861093536"><a name="p1303690861093536"></a><a name="p1303690861093536"></a>uint32_t </p>
</td>
</tr>
<tr id="row630413332093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1940727692093536"><a name="p1940727692093536"></a><a name="p1940727692093536"></a><a href="programinfo.md#a7464c64a9cdbd91debb2e0dc3ae494bd">track</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1909747609093536"><a name="p1909747609093536"></a><a name="p1909747609093536"></a><a href="trackinfo.md">TrackInfo</a> * </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1869961120093536"></a>

## **Field Documentation**<a name="section863690521093536"></a>

## durationMs<a name="a652dc8e396a6c8337f24ef19a60ff8d5"></a>

```
int64_t ProgramInfo::durationMs
```

 **Description:**

Program duration 

## programId<a name="a37665885745484c665fd7c3f7c4e0257"></a>

```
int32_t ProgramInfo::programId
```

 **Description:**

Program index 

## track<a name="a7464c64a9cdbd91debb2e0dc3ae494bd"></a>

```
[TrackInfo](trackinfo.md)* ProgramInfo::track
```

 **Description:**

Pointer to the array of current program information 

## trackNum<a name="a63ffbb3059e57c139cb3801c8188c662"></a>

```
uint32_t ProgramInfo::trackNum
```

 **Description:**

Number of tracks of the current program 

